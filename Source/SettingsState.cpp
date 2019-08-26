#include "SettingsState.h"

SettingsState::SettingsState(weak_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys, std::stack<unique_ptr<State>>* states)
	:State(window, supported_keys, states)
{
	this->InitFonts();
	this->InitKeybinds();
	this->InitButtons();
	this->InitBackground();
}

SettingsState::~SettingsState()
{
	std::cout << "Destructor " << __func__ << "\n";
}

void SettingsState::InitBackground()
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

void SettingsState::InitFonts()
{
	if (!font_dosis.loadFromFile("Data/Fonts/Dosis-Light.ttf"))
	{
		std::cout << "\nError! MainMenu::InitFonts()! Dosis\n";
		throw "Error! MainMenu::InitFonts()! Dosis";
	}
}

void SettingsState::InitButtons()
{
	buttons["Quit"] = make_unique<gui::Button>(120, 720, 150, 50, "Quit", &this->font_dosis);
	dl = make_shared<gui::DropList>(900, 200, 100, 50,  font_dosis, std::vector<string>{"4x", "8x", "16x"} );
}

void SettingsState::UpdateButtons(const float& frame_time)
{
	for (const auto& [name,button] : buttons)
	{
		button->Update(mouse_pos_view, frame_time);
	}

	if (buttons.contains("Quit") && buttons.at("Quit")->IsPressed())
	{
		this->EndState();
		this->bQuit = true;
	}
	if (dl.get())
		dl->Update(mouse_pos_view,frame_time);
	
}

void SettingsState::RenderButtons(sf::RenderWindow* window)
{
	for (const auto& [name,button] : buttons)
	{
		button->Render(window);
	}

	if (dl.get())
		dl->Render(window);
}

void SettingsState::EndState()
{
	std::ofstream ofs("Config/keybinds.ini");
	if (ofs.is_open())
	{
		ofs << "MOVE_LEFT " << current_keybinds["MOVE_LEFT"]
			<< "\n" << "MOVE_RIGHT " << current_keybinds["MOVE_RIGHT"]
			<< "\n" << "MOVE_UP " << current_keybinds["MOVE_UP"]
			<< "\n" << "MOVE_DOWN " << current_keybinds["MOVE_DOWN"]
			<< "\n" << "QUIT " << current_keybinds["QUIT"];
	}
	ofs.close();
}

void SettingsState::InitKeybinds()
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

void SettingsState::UpdateInput(const float& frame_time)
{
}

void SettingsState::Update(const float& frame_time)
{
	this->UpdateInput(frame_time);
	this->UpdateMousePos();
	this->UpdateButtons(frame_time);
}

void SettingsState::Render(sf::RenderWindow* target)
{
	this->window->draw(background_s);
	this->RenderButtons(window.get());


	sf::Text mouse_text;
	mouse_text.setPosition(sf::Vector2f(mouse_pos_view.x + 15, mouse_pos_view.y)); // +15 for better position. Now mouse dont cover a text
	mouse_text.setFont(font_dosis);
	mouse_text.setCharacterSize(15);

	string mouse_pos = "X: " + to_string((int)mouse_pos_view.x) + " Y: " + to_string((int)mouse_pos_view.y);
	mouse_text.setString(mouse_pos);


	this->window->draw(mouse_text);
}
