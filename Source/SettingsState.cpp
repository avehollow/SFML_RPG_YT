#include "pch.h"
#include "SettingsState.h"

SettingsState::SettingsState(shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys, std::stack<unique_ptr<State>>* states)
	: State(window, supported_keys, states)
	, video_modes(sf::VideoMode::getFullscreenModes())
{
	current_setting.width		   = 1920;
	current_setting.height		   = 1080;
	current_setting.bpp			   = 32;
	current_setting.bFullScreen    = 1;


	this->InitFonts();
	this->InitKeybinds();
	this->InitGui();
	this->InitBackground();

}

SettingsState::~SettingsState()
{
	std::cout << "\nDestructor " << __func__ << "\n";
}

void SettingsState::InitBackground()
{
	if (background_t.loadFromFile("Resource/Image/Background/background.png"))
	{
		std::cout << "\nWindow size: X:" << window->getSize().x << " Y: " << window->getSize().y;
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

void SettingsState::InitGui()
{
	std::vector<string> video;
	video.reserve(video_modes.size());

	int i = 2;
	for (const auto& el:video_modes )
	{
		if (i++%2 == 0 && el.bitsPerPixel == 32)	
			video.push_back(std::to_string(el.width) + "x" + std::to_string(el.height) + "p" + std::to_string(el.bitsPerPixel));
		
	}
	


	buttons["Back"]  = make_unique<gui::Button>(
		  window->getSize().x * 0.1f
		, window->getSize().y * 0.9f
		, 150
		, 50
		,"Back"
		, &font_dosis);

	buttons["Apply"] = make_unique<gui::Button>(
		  window->getSize().x * 0.8f
		, window->getSize().y * 0.9f
		, 150
		, 50
		, "Apply"
		, &font_dosis);
	
	drop_lists["Resolution"] = make_shared<gui::DropList>(
		  window->getSize().x * 0.6f
		, window->getSize().y * 0.3f
		, 100
		, 50
		, font_dosis
		, video
		, "Resolution: ");

	drop_lists["Fullscreen"] = make_shared<gui::DropList>(
		  window->getSize().x * 0.8f
		, window->getSize().y * 0.3f
		, 100
		, 50
		, font_dosis
		, std::initializer_list<string>{"ON", "OFF"}
		, "Full screen: "
		, !current_setting.bFullScreen);

	drop_lists["Resolution"]->GetActiveElement()->text.setString(
		std::to_string(current_setting.width)  +
		"x"									   +
		std::to_string(current_setting.height) +
		"p"									   + 
		std::to_string(current_setting.bpp));

}

void SettingsState::UpdateGui(const float& frame_time)
{
	for (const auto& [name,button] : buttons)
	{
		button->Update(mouse_pos_view, frame_time);
	}

	for (const auto& [name, droplist] : drop_lists)
	{
		droplist->Update(mouse_pos_view, frame_time);
	}

	if (buttons.contains("Back") && buttons.at("Back")->IsPressed())
	{
		this->EndState();
		this->bQuit = true;
	}
	


	if (buttons.contains("Apply") && buttons["Apply"]->IsPressed())
	{
		if (drop_lists.contains("Fullscreen"))
		{
			string text = drop_lists["Fullscreen"]->GetActiveElement()->text.getString().toAnsiString();

			if (text.find("ON") != string::npos)
				current_setting.bFullScreen = true;
			else
				current_setting.bFullScreen = false;
		}

		if (drop_lists.contains("Resolution"))
		{
			string text = drop_lists["Resolution"]->GetActiveElement()->text.getString().toAnsiString();
			size_t _idx = 0;

		    current_setting.width = std::stoi(text, &_idx);
			text.erase(0, _idx+1) ;
			current_setting.height = std::stoi(text, &_idx);
			text.erase(0, _idx + 1);
			current_setting.bpp = std::stoi(text, &_idx);
		}
		if (current_setting.bFullScreen)
			window->create(sf::VideoMode(current_setting.width, current_setting.height, current_setting.bpp), "SFML_RPG", sf::Style::Fullscreen);
		else
			window->create(sf::VideoMode(current_setting.width, current_setting.height, current_setting.bpp), "SFML_RPG", sf::Style::Titlebar | sf::Style::Close);
		
		// AVE lock framerate
		// Bad idea
		window->setFramerateLimit(60);
		window->setVerticalSyncEnabled(false);

		bQuit = true;
	}

}

void SettingsState::RenderGui(sf::RenderWindow* window)
{
	for (const auto& [name,button] : buttons)
	{
		button->Render(window);
	}

	for (const auto& [name, droplist] : drop_lists)
	{
		droplist->Render(window);
	}
}

void SettingsState::EndState()
{
	std::ofstream ofs("Config/keybinds.ini");
	if (ofs.is_open())
	{
		ofs << "MOVE_LEFT " << current_keybinds["MOVE_LEFT"]
			<< "\nMOVE_RIGHT " << current_keybinds["MOVE_RIGHT"]
			<< "\nMOVE_UP " << current_keybinds["MOVE_UP"]
			<< "\nMOVE_DOWN " << current_keybinds["MOVE_DOWN"]
			<< "\nQUIT " << current_keybinds["QUIT"];
	}
	ofs.close();

	ofs.open("Config/settings.ini");
	if (ofs.is_open())
	{
		ofs << "WIDTH "		  << current_setting.width   
			<< "\nHEIGHT "	  << current_setting.height  
			<< "\nBPP "		  << current_setting.bpp     
			<< "\nFullScreen "<< current_setting.bFullScreen;
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

	ifs.open("Config/settings.ini");
	if (ifs.is_open())
	{
		std::string setting_name;
		int value;
		int i = 0;
		
		while (ifs >> setting_name >> value)
		{
			current_setting.parm[i++] = value;
		}
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
	this->UpdateGui(frame_time);
}

void SettingsState::Render(sf::RenderWindow* target)
{
	this->window->draw(background_s);
	this->RenderGui(window.get());


	sf::Text mouse_text;
	mouse_text.setPosition(sf::Vector2f(mouse_pos_view.x + 15, mouse_pos_view.y)); // +15 for better position. Now mouse dont cover a text
	mouse_text.setFont(font_dosis);
	mouse_text.setCharacterSize(15);

	string mouse_pos = "X: " + to_string((int)mouse_pos_view.x) + " Y: " + to_string((int)mouse_pos_view.y);
	mouse_text.setString(mouse_pos);


	this->window->draw(mouse_text);
}
