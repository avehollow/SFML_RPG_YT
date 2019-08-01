#include "MainMenu.h"

//HACK Why i sent suported_keys to State.h if i in this place fill map keybinds? After this i dont need sent supported_keys to State
MainMenu::MainMenu(weak_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys, std::stack<unique_ptr<State>>* states)
	: State(window, supported_keys, states)
{
	this->InitFonts();
	this->InitKeybinds();
	this->InitButtons();
	this->InitBackground();

}

MainMenu::~MainMenu()
{
	std::cout << "\nDestructor MainMenu::~MainMenu()\n";
}



void MainMenu::InitBackground()
{
	if (background_t.loadFromFile("Resource/Image/Background/background.png"))
	{
		background_s.setSize(sf::Vector2f(window->getSize()));
		background_s.setTexture(&background_t);
	}
	else
	{
		std::cout << "\nERROR !\nCANT LOAD TEXTURE BACKGROUND\n";
	}
}

void MainMenu::InitFonts()
{
	if (!font_dosis.loadFromFile("Data/Fonts/Dosis-Light.ttf"))
	{
		std::cout << "\nError! MainMenu::InitFonts()! Dosis\n";
		throw "Error! MainMenu::InitFonts()! Dosis";
	}
}

void MainMenu::InitButtons()
{
	buttons["New Game"]		  = make_unique<Button>(150, 450, 150, 50, "New Game",		 &this->font_dosis);
	buttons["Options"]        = make_unique<Button>(150, 550, 150, 50, "Options",        &this->font_dosis);
	buttons["Quit"]			  = make_unique<Button>(150, 850, 150, 50, "Quit",			 &this->font_dosis);
}

void MainMenu::UpdateButtons(const float& frame_time)
{
	for (const auto& button : buttons)
	{
		button.second->Update(mouse_pos_view, frame_time);
	}

	if (buttons.at("New Game")->IsPressed())
	{
		states->push(make_unique<GameState>(window, supported_keys, states)); // states and supported_keyds is pointer
	}

	if (buttons.at("Quit")->IsPressed())
	{
		this->bQuit = true;
	}
}

void MainMenu::RenderButtons(sf::RenderWindow* window)
{
	for (const auto& button : buttons)
	{
		button.second->Render(window);
	}
}

void MainMenu::EndState()
{
	std::ofstream ofs("Config/keybinds.ini");
	if (ofs.is_open())
	{
		ofs << "MOVE_LEFT "			 << current_keybinds["MOVE_LEFT"]
			<< "\n" << "MOVE_RIGHT " << current_keybinds["MOVE_RIGHT"]
			<< "\n" << "MOVE_UP "	 << current_keybinds["MOVE_UP"]
			<< "\n" << "MOVE_DOWN "  << current_keybinds["MOVE_DOWN"]
			<< "\n" << "QUIT "       << current_keybinds["QUIT"];
	}
	ofs.close();
}

void MainMenu::InitKeybinds()
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

void MainMenu::UpdateMousePos()
{
	State::UpdateMousePos();
}

void MainMenu::UpdateInput(const float& frame_time)
{

}

void MainMenu::Update(const float& frame_time)
{
	this->UpdateInput(frame_time);
	this->UpdateMousePos();
	this->UpdateButtons(frame_time);
}

void MainMenu::Render(sf::RenderWindow* window)
{
	this->window->draw(background_s);
	this->RenderButtons(window);


	sf::Text mouse_text;
	mouse_text.setPosition(sf::Vector2f(mouse_pos_view.x + 15, mouse_pos_view.y )); // +15 for better position. Now mouse dont cover a text
	mouse_text.setFont(font_dosis);
	mouse_text.setCharacterSize(15);

	string mouse_pos = "X: " + to_string((int)mouse_pos_view.x) + " Y: "+ to_string((int)mouse_pos_view.y);
	mouse_text.setString(mouse_pos);
	

	this->window->draw(mouse_text);
}

