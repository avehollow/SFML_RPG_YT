#include "GameState.h"

//HACK Why i sent suported_keys to State.h if i in this place fill map keybinds? After this i dont need sent supported_keys to State
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supported_keys)
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
}

void GameState::CheckForQuit()
{
	State::CheckForQuit();
}

void GameState::InitKeybinds()
{
	keybinds.emplace("MOVE_LEFT",  supported_keys->at("A"));
	keybinds.emplace("MOVE_RIGHT", supported_keys->at("D"));
	keybinds.emplace("MOVE_UP",    supported_keys->at("W"));
	keybinds.emplace("MOVE_DOWN",  supported_keys->at("S"));
}

void GameState::UpdateInput(const float& frame_time)
{
	this->CheckForQuit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->player.move(frame_time, -1.0f, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		this->player.move(frame_time, +1.0f, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->player.move(frame_time, 0.0f, -1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		this->player.move(frame_time, 0.0f, +1.0f);
	}
}

void GameState::Update(const float& frame_time)
{
	this->UpdateInput(frame_time);
	player.Update(frame_time);
}

void GameState::Render(sf::RenderTarget* target)
{
	player.Render(target);
}
