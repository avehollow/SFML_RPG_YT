#include "EditorState.h"


//HACK Why i sent suported_keys to State.h if i in this place fill map keybinds? After this i dont need sent supported_keys to State
EditorState::EditorState(weak_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys, std::stack<unique_ptr<State>>* states)
	: State(window, supported_keys, states)
{
	this->InitFonts();
	this->InitKeybinds();
	this->InitButtons();
	this->InitBackground();

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

void EditorState::EndState()
{
	std::ofstream ofs("Config/keybinds.ini");
	if (ofs.is_open())
	{
		ofs << "MOVE_LEFT "			 << current_keybinds["MOVE_LEFT"]
			<< "\n" << "MOVE_RIGHT " << current_keybinds["MOVE_RIGHT"]
			<< "\n" << "MOVE_UP "    << current_keybinds["MOVE_UP"]
			<< "\n" << "MOVE_DOWN "  << current_keybinds["MOVE_DOWN"]
			<< "\n" << "QUIT "		 << current_keybinds["QUIT"];
	}
	ofs.close();
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("QUIT"))))
	{
		bQuit = true;
	}
}

void EditorState::Update(const float& frame_time)
{
	this->UpdateInput(frame_time);
	this->UpdateMousePos();
	this->UpdateButtons(frame_time);
}

void EditorState::Render(sf::RenderWindow* window)
{
	this->window->draw(background_s);
	this->RenderButtons(window);


	sf::Text mouse_text;
	mouse_text.setPosition(sf::Vector2f(mouse_pos_view.x + 15, mouse_pos_view.y)); // +15 for better position. Now mouse dont cover a text
	mouse_text.setFont(font_dosis);
	mouse_text.setCharacterSize(15);

	string mouse_pos = "X: " + to_string((int)mouse_pos_view.x) + " Y: " + to_string((int)mouse_pos_view.y);
	mouse_text.setString(mouse_pos);


	this->window->draw(mouse_text);
}

