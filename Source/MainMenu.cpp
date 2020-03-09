#include "pch.h"
#include "MainMenu.h"

//HACK Why i sent suported_keys to State.h if i in this place fill map keybinds? After this i dont need sent supported_keys to State
MainMenu::MainMenu(StateData* state_data)
	: State(state_data)
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
	if (background_t.loadFromFile("Resource/Image/Background/background2.png"))
	{
		background_s.setSize(sf::Vector2f(window->getSize()));
		background_s.setTexture(&background_t);
	}
	else
	{
		std::cout << "\nERROR !\nCANT LOAD TEXTURE BACKGROUND\n";
	}

	blackarea.setFillColor(sf::Color(10,10,10,225));
	blackarea.setPosition(250, 0);
	blackarea.setSize(sf::Vector2f(350, window->getSize().y));
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
	buttons["New Game"]       = make_unique<gui::Button>(120, 320, 150, 50, "New Game",      &this->font_dosis);
	buttons["Options"]        = make_unique<gui::Button>(120, 420, 150, 50, "Options",       &this->font_dosis);
	buttons["Editor"]         = make_unique<gui::Button>(120, 520, 150, 50, "Editor",        &this->font_dosis);
	buttons["Quit"]			  = make_unique<gui::Button>(120, 720, 150, 50, "Quit",			 &this->font_dosis);
}

void MainMenu::UpdateButtons(const float& frame_time)
{
	blackarea.setPosition(window->getSize().x * 0.10f, 0);
	blackarea.setSize(sf::Vector2f(350 * (float)window->getSize().x / 1920.f, window->getSize().y));

	//HLOG Maybe create better solution to calculate right scale, because currently depend on 1920px and 1080px ?
	buttons["New Game"]->SetTextScale((float)window->getSize().x /1920.f, (float)window->getSize().y / 1080.f);
	buttons["Options"] ->SetTextScale((float)window->getSize().x /1920.f, (float)window->getSize().y / 1080.f);
	buttons["Editor"]  ->SetTextScale((float)window->getSize().x /1920.f, (float)window->getSize().y / 1080.f);
	buttons["Quit"]    ->SetTextScale((float)window->getSize().x /1920.f, (float)window->getSize().y / 1080.f);

	//HLOG I need both function to UpdateButtons (SetPostion and SetScale)
	// After some updates
	// At this time, we need to separatelty adjust the size of the text and shape button
	buttons["New Game"]->SetSizeShape(150 * (float)window->getSize().x / 1920.f,50* (float)window->getSize().y / 1080.f);
	buttons["Options"] ->SetSizeShape(150 * (float)window->getSize().x / 1920.f,50* (float)window->getSize().y / 1080.f);
	buttons["Editor"]  ->SetSizeShape(150 * (float)window->getSize().x / 1920.f,50* (float)window->getSize().y / 1080.f);
	buttons["Quit"]	   ->SetSizeShape(150 * (float)window->getSize().x / 1920.f,50* (float)window->getSize().y / 1080.f);

	buttons["New Game"]->SetPosition((blackarea.getPosition().x + (blackarea.getSize().x / 2)) - (buttons["New Game"]->GetSize().x / 2) /* or use funnction -> per2pixX(10.0f)*/ , window->getSize().y * 0.3f);
	buttons["Options"] ->SetPosition((blackarea.getPosition().x + (blackarea.getSize().x / 2)) - (buttons["Options"] ->GetSize().x / 2) /* or use funnction -> per2pixX(10.0f)*/ , window->getSize().y * 0.40f);
	buttons["Editor"]  ->SetPosition((blackarea.getPosition().x + (blackarea.getSize().x / 2)) - (buttons["Editor"]  ->GetSize().x / 2) /* or use funnction -> per2pixX(10.0f)*/ , window->getSize().y * 0.50f);
	buttons["Quit"]    ->SetPosition((blackarea.getPosition().x + (blackarea.getSize().x / 2)) - (buttons["Quit"]    ->GetSize().x / 2) /* or use funnction -> per2pixX(10.0f)*/ , window->getSize().y * 0.70f);



	for (const auto& [name,button] : buttons){
		button->Update(sf::Vector2f(mouse_pos_window), frame_time);
	}


	if (buttons.contains("New Game") && buttons.at("New Game")->IsPressed()) states->push(make_unique<GameState>(state_data));                       
	if (buttons.contains("Editor")   && buttons.at("Editor")->IsPressed())     states->push(make_unique<EditorState>(state_data));
	if (buttons.contains("Options")  && buttons.at("Options")->IsPressed())   states->push(make_unique<SettingsState>(state_data));
	if (buttons.contains("Quit")     && buttons.at("Quit")->IsPressed()) this->bQuit = true;
	
}

void MainMenu::RenderButtons(sf::RenderWindow* window)
{
	for (const auto& [name,button] : buttons)
	{
		button->Render(window);
	}
}

void MainMenu::EndState()
{
	//std::ofstream ofs("Config/keybinds.ini");
	//if (ofs.is_open())
	//{
	//	ofs << "MOVE_LEFT "			 << current_keybinds["MOVE_LEFT"]
	//		<< "\n" << "MOVE_RIGHT " << current_keybinds["MOVE_RIGHT"]
	//		<< "\n" << "MOVE_UP "	 << current_keybinds["MOVE_UP"]
	//		<< "\n" << "MOVE_DOWN "  << current_keybinds["MOVE_DOWN"]
	//		<< "\n" << "QUIT "       << current_keybinds["QUIT"];
	//}
	//ofs.close();
}

void MainMenu::InitKeybinds()
{
	std::ifstream ifs("Config/keybinds.ini");
	if (ifs.is_open())
	{
		std::string name_action;
		//std::string key;
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

void MainMenu::UpdateMousePos(sf::View* view)
{
	State::UpdateMousePos();
}

void MainMenu::UpdateInput(const float& frame_time)
{

}

void MainMenu::Update(const float& frame_time)
{
	// HACK because if we resize window we must update background texture
	background_s.setSize(sf::Vector2f(window->getSize()));

	
	this->UpdateInput(frame_time);
	this->UpdateMousePos();
	this->UpdateButtons(frame_time);
}

void MainMenu::Render(sf::RenderWindow* window)
{
	this->window->draw(background_s);
	this->window->draw(blackarea);
	this->RenderButtons(window);


	sf::Text mouse_text;
	mouse_text.setPosition(sf::Vector2f(mouse_pos_view.x + 15, mouse_pos_view.y )); // +15 for better position. Now mouse dont cover a text
	mouse_text.setFont(font_dosis);
	mouse_text.setCharacterSize(15);

	string mouse_pos = "X: " + to_string((int)mouse_pos_view.x) + " Y: "+ to_string((int)mouse_pos_view.y);
	mouse_text.setString(mouse_pos);
	

	this->window->draw(mouse_text);
}

