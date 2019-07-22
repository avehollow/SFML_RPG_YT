#include "MainMenu.h"

//HACK Why i sent suported_keys to State.h if i in this place fill map keybinds? After this i dont need sent supported_keys to State
MainMenu::MainMenu(weak_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys)
	: State(window, supported_keys)
{
	this->InitFonts();
	this->InitKeybinds();

	background.setSize(static_cast<sf::Vector2f>( window.lock()->getSize() ));
	background.setFillColor(sf::Color::Magenta);

	button = make_unique<Button>(100, 100, 50, 75, "Przycisk", &this->font_dosis);
}

MainMenu::~MainMenu()
{
	std::cout << "\nDestructor MainMenu::~MainMenu()\n";
}



void MainMenu::InitFonts()
{
	if (!font_dosis.loadFromFile("Data/Fonts/Dosis-Light.ttf"))
	{
		std::cout << "\nError! MainMenu::InitFonts()! Dosis\n";
		throw "Error! MainMenu::InitFonts()! Dosis";
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
void MainMenu::CheckForQuit()
{
	State::CheckForQuit();
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
	this->CheckForQuit();

}

void MainMenu::Update(const float& frame_time)
{
	this->UpdateInput(frame_time);
	this->UpdateMousePos();
	button->Update(mouse_pos_view);
}

void MainMenu::Render(sf::RenderWindow* window)
{
	this->window->draw(background);
	button->Render(window);
}

