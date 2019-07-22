#include "GameState.h"

//HACK Why i sent suported_keys to State.h if i in this place fill map keybinds? After this i dont need sent supported_keys to State
GameState::GameState(weak_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys)
	: State(window, supported_keys)
{
	this->InitKeybinds();

}

GameState::~GameState()
{
	std::cout << "\nDestructor GameState::~GameState()\n";
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
void GameState::CheckForQuit()
{
	State::CheckForQuit();
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
	this->CheckForQuit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("MOVE_LEFT"))))
	{
		this->player.move(frame_time, -1.0f, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("MOVE_RIGHT"))))
	{
		this->player.move(frame_time, +1.0f, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("MOVE_UP"))))
	{
		this->player.move(frame_time, 0.0f, -1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("MOVE_DOWN"))))
	{
		this->player.move(frame_time, 0.0f, +1.0f);
	}
}

void GameState::Update(const float& frame_time)
{
	this->UpdateMousePos();
	this->UpdateInput(frame_time);
	player.Update(frame_time);
}

void GameState::Render(sf::RenderWindow* target)
{
	player.Render(target);
}
