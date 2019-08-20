#include "GameState.h"

//HACK Why i sent suported_keys to State.h if i in this place fill map keybinds? After this i dont need sent supported_keys to State
GameState::GameState(weak_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys, std::stack<unique_ptr<State>>* states)
	: State(window, supported_keys, states), pause_menu(window.lock().get(), font_dosis)
{
	this->InitKeybinds();
	this->InitTextures();

	this->InitSprites();
	player = make_shared<Player>(20, 20, &sprites["PLAYER"], &textures["PLAYER"]);

	this->InitPauseMenu();
}

GameState::~GameState()
{
	std::cout << "\nDestructor GameState::~GameState()\n";
}

void GameState::InitTextures()
{
	textures["PLAYER"].loadFromFile("Resource/Image/Sprites/Player/PLAYER_SHEET.png");
}

void GameState::InitSprites()
{
	sprites["PLAYER"].setTexture(textures["PLAYER"]);
	// Works. Create new sprite!
	//sprites["PLAYER1"].setTexture(textures["PLAYER"]);
	//sprites["PLAYER2"].setTexture(textures["PLAYER"]);
	std::cout <<"\n\nCount sprites: "<< sprites.size();
}



void GameState::InitPauseMenu()
{
	pause_menu.AddButton("Quit",   0.0f, window.get()->getSize().y - 250.0f, "Quit"  );
	pause_menu.AddButton("Resume", 0.0f, 250.0f,                             "Resume");
}

void GameState::UpdatePauseMenuInput()
{
	if (pause_menu.IsButtonPressed("Quit"))     bQuit = true;

	if (pause_menu.IsButtonPressed("Resume"))	bPause = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("QUIT"))) && KeyTime())
	{
		if (bPause) bPause = false;
	}
	
}

void GameState::EndState()
{
	std::ofstream ofs("Config/keybinds.ini");
	if (ofs.is_open())
	{
		ofs << "MOVE_LEFT "			 << current_keybinds["MOVE_LEFT"]
			<< "\n" << "MOVE_RIGHT " << current_keybinds["MOVE_RIGHT"]
			<< "\n" << "MOVE_UP "    << current_keybinds["MOVE_UP"]
			<< "\n" << "MOVE_DOWN "  << current_keybinds["MOVE_DOWN"]
			<< "\n" << "QUIT "       << current_keybinds["QUIT"];
	}
	ofs.close();
}


void GameState::InitKeybinds()
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

void GameState::UpdateMousePos()
{
	State::UpdateMousePos();
}

void GameState::UpdateInput(const float& frame_time)
{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("MOVE_LEFT"))))
		{
			this->player->move(frame_time, -1.0f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("MOVE_RIGHT"))))
		{
			this->player->move(frame_time, +1.0f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("MOVE_UP"))))
		{
			this->player->move(frame_time, 0.0f, -1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("MOVE_DOWN"))))
		{
			this->player->move(frame_time, 0.0f, +1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("QUIT"))) && KeyTime())
		{
			if (!bPause) bPause = true;
		}
}

void GameState::Update(const float& frame_time)
{
	this->UpdateMousePos(); 
	this->UpdateKeyTime(frame_time);

	if (bPause)
	{
		this->UpdatePauseMenuInput();
		pause_menu.Update(mouse_pos_view, frame_time);
	}
	else
	{ 
		this->UpdateInput(frame_time);
		player->Update(frame_time);
	}
}

void GameState::Render(sf::RenderWindow* target)
{
	player->Render(target);
	if (bPause)
	{
		pause_menu.Render(target);
	}
}
