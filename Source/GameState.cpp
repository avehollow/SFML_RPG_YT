#include "pch.h"
#include "GameState.h"
#include "SettingsState.h"

//HACK Why i sent suported_keys to State.h if i in this place fill map keybinds? After this i dont need sent supported_keys to State
GameState::GameState(StateData* state_data)
	: State(state_data), pause_menu(window.get(), font_dosis)
	, map(nullptr)
{
	this->InitKeybinds();
	this->InitTextures();

	this->InitSprites();
	player = make_shared<Player>(20, 20, &sprites["PLAYER"], &textures["PLAYER"]);

	this->InitPauseMenu();

	texture_sheet.loadFromFile("Resource/Image/Sprites/Tiles/tilesheet1.png");
	map.SetTextureSheet(&texture_sheet);
	map.LoadFromFile();

	this->InitView();
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

void GameState::InitView()
{
	view.setSize(sf::Vector2f(window->getSize()));
	view.setCenter(
				   window->getSize().x / 2.0f,
				   window->getSize().y / 2.0f
	);
	    std::cout << "\n Rozmiar okna X: " << window->getSize().x;
		std::cout << "\n Rozmiar okna Y: " << window->getSize().y;
}



void GameState::InitPauseMenu()
{
	pause_menu.AddButton("Resume",  250.0f,                             "Resume");
	pause_menu.AddButton("Options", window.get()->getSize().y - 500.0f, "Options"  );
	pause_menu.AddButton("Quit",    window.get()->getSize().y - 250.0f, "Quit"  );
}

void GameState::UpdatePauseMenuInput()
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
	
}

void GameState::UpdateView()
{
	// AVE Use intengers values to move view because using float causes flickering tile textures!
	view.setCenter(std::floor(player->GetPosition().x), std::floor(player->GetPosition().y));
}

void GameState::EndState()
{

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

void GameState::UpdateMousePos(sf::View* view)
{
	State::UpdateMousePos(view);
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
	this->UpdateMousePos(&view); 
	this->UpdateKeyTime(frame_time);

	if (bPause)
	{
		this->UpdatePauseMenuInput();
		pause_menu.Update(sf::Vector2f(mouse_pos_window), frame_time);
	}
	else
	{ 
		this->UpdateView();
		this->UpdateInput(frame_time);
		//AVE VERY IMPORTANT!!! Check collision before update player
		map.UpdateCollision(player.get(),frame_time);
		player->Update(frame_time);
	}
}

void GameState::Render(sf::RenderWindow* target)
{
	if (!target)
		return;
	
	target->setView(view);

	map.Render(target, player.get());
	player->Render(target);
	if (bPause)
	{
		target->setView(window->getDefaultView());
		pause_menu.Render(target);
	}
}
