#include "pch.h"
#include "EditorState.h"
#include "SettingsState.h"

//HACK Why i sent suported_keys to State.h if i in this place fill map keybinds? After this i dont need sent supported_keys to State
EditorState::EditorState(StateData* state_data)
	: State(state_data)
	, pause_menu(window.get(),font_dosis)
	, map(&texture_sheet)
	, texture_selector(10,10, 900, 200, 100)
{
	this->InitFonts();
	this->InitKeybinds();
	this->InitButtons();
	this->InitBackground();
	this->InitPauseMenu();


	selected_tile.setOutlineColor(sf::Color::Red);
	selected_tile.setOutlineThickness(1.0f);
	selected_tile.setSize(sf::Vector2f(state_data->tile_size, state_data->tile_size));

	texture_sheet.loadFromFile("Resource/Image/Sprites/Tiles/tilesheet1.png");
	texture_selector.SetTexture(&texture_sheet);

	texture_rect.height = 100;
	texture_rect.width  = 100;
	texture_rect.top    = 0;
	texture_rect.left   = 0;

}

EditorState::~EditorState()
{
	std::cout << "\nDestructor EditorState::~EditorState()\n";
}



void EditorState::InitBackground()
{

}

void EditorState::InitFonts()
{
	if (!font_dosis.loadFromFile("Data/Fonts/Dosis-Light.ttf"))
	{
		std::cout << "\nError! EditorState::InitFonts()! Dosis\n";
		throw "Error! EditorState::InitFonts()! Dosis";
	}
}

void EditorState::InitButtons()
{

}

void EditorState::UpdateButtons(const float& frame_time)
{

}

void EditorState::RenderButtons(sf::RenderWindow* window)
{

}

void EditorState::InitPauseMenu()
{
	pause_menu.AddButton("Resume",  250.0f, "Resume");
	pause_menu.AddButton("Options", window.get()->getSize().y - 500.0f, "Options");
	pause_menu.AddButton("Quit",    window.get()->getSize().y - 250.0f, "Quit");
}

void EditorState::UpdatePauseMenuInput()
{
	if (pause_menu.IsButtonPressed("Quit"))     bQuit = true;

	if (pause_menu.IsButtonPressed("Resume"))	bPause = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("QUIT"))) && KeyTime())
	{
		if (bPause) bPause = false;
	}

	if (pause_menu.IsButtonPressed("Options"))
	{
		states->push(make_unique<SettingsState>(state_data));
	}
	
};


void EditorState::EndState()
{

}

void EditorState::InitKeybinds()
{
	std::ifstream ifs("Config/keybinds.ini");
	if (ifs.is_open())
	{
		std::string name_action;
		int key;
		while (ifs >> name_action >> key)
		{
			current_keybinds[name_action] = key;
		}
	}
	else
	{
		//HACK MessageBox ?
	}
	ifs.close();
}

void EditorState::UpdateMousePos()
{
	State::UpdateMousePos();
	selected_tile.setPosition(mouse_pos_grid.x * state_data->tile_size, mouse_pos_grid.y * state_data->tile_size);
}

void EditorState::UpdateInput(const float& frame_time)
{
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("QUIT"))))
	//{
	//	bQuit = true;
	//}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("QUIT"))) && KeyTime())
	{
		if (!bPause) bPause = true;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && KeyTime())
	{
		map.AddTile(mouse_pos_grid.x, mouse_pos_grid.y, layer, texture_rect);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && KeyTime())
	{
		map.RemoveTile(mouse_pos_grid.x, mouse_pos_grid.y, layer);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) layer = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) layer = 1;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) layer = 2;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && KeyTime())
	{
		if (texture_rect.left - 100 >= 0)
		{
			texture_rect.left -= 100;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && KeyTime())
	{
		if (texture_rect.left + 100 <= texture_sheet.getSize().x - 100)
		{
			texture_rect.left += 100;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && KeyTime())
	{
		if (texture_rect.top - 100 >= 0)
		{
			texture_rect.top -= 100;
		}

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && KeyTime())
	{
		if (texture_rect.top + 100 <= texture_sheet.getSize().y - 100)
		{
			texture_rect.top += 100;
		}
	}
	

}

void EditorState::Update(const float& frame_time)
{
	this->UpdateKeyTime(frame_time);
	this->UpdateMousePos();
	if (bPause)
	{
		this->UpdatePauseMenuInput();
		pause_menu.Update(mouse_pos_view, frame_time);
	}
	else
	{
		this->UpdateInput(frame_time);
		this->UpdateButtons(frame_time);
		map.Update(frame_time);
		texture_selector.Update(frame_time, mouse_pos_view);
	}
	selected_tile.setTexture(&texture_sheet);
	selected_tile.setTextureRect(texture_rect);
	selected_tile.setFillColor(sf::Color(
		selected_tile.getFillColor().r,
		selected_tile.getFillColor().g,
		selected_tile.getFillColor().b,
		100));

}

void EditorState::Render(sf::RenderWindow* window)
{
	this->window->draw(background_s);
	map.Render(window);

	sf::Text mouse_text;
	mouse_text.setPosition(sf::Vector2f(mouse_pos_view.x + 15, mouse_pos_view.y)); // +15 for better position. Now mouse dont cover a text
	mouse_text.setFont(font_dosis);
	mouse_text.setCharacterSize(15);

	string mouse_pos =  "X: "    + to_string((int)mouse_pos_view.x) + " Y: "  + to_string((int)mouse_pos_view.y);
	       mouse_pos += "\nTX: " + to_string(mouse_pos_grid.x)      + " TY: " + to_string(mouse_pos_grid.y);
		   mouse_pos += "\nL: "  + to_string(layer+1);
	mouse_text.setString(mouse_pos);
	mouse_text.setOutlineColor(sf::Color::Black);
	mouse_text.setOutlineThickness(1);
	
	texture_selector.Render(window);

	if (bPause)
	{
		pause_menu.Render(window);
	}
	else
	{
		this->RenderButtons(window);
		window->draw(selected_tile);
	}
	
	this->window->draw(mouse_text);
}

