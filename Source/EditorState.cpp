#include "pch.h"
#include "EditorState.h"
#include "SettingsState.h"

//HACK Why i sent suported_keys to State.h if i in this place fill map keybinds? After this i dont need sent supported_keys to State
EditorState::EditorState(shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys, std::stack<unique_ptr<State>>* states)
	: State(window, supported_keys, states)
	, pause_menu(window.get(),font_dosis)
{
	this->InitFonts();
	this->InitKeybinds();
	this->InitButtons();
	this->InitBackground();
	this->InitPauseMenu();

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
		states->push(make_unique<SettingsState>(window, supported_keys, states));
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
	}
}

void EditorState::Render(sf::RenderWindow* window)
{
	this->window->draw(background_s);
	map.Render(window);

	this->RenderButtons(window);


	sf::Text mouse_text;
	mouse_text.setPosition(sf::Vector2f(mouse_pos_view.x + 15, mouse_pos_view.y)); // +15 for better position. Now mouse dont cover a text
	mouse_text.setFont(font_dosis);
	mouse_text.setCharacterSize(15);

	string mouse_pos = "X: " + to_string((int)mouse_pos_view.x) + " Y: " + to_string((int)mouse_pos_view.y);
	mouse_text.setString(mouse_pos);

	if (bPause) pause_menu.Render(window);
	

	this->window->draw(mouse_text);
}

