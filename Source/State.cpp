#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supported_keys)
{
	this->window		 = window;
	this->supported_keys = supported_keys;
}

State::~State()
{
	std::cout << "Destructor State::~State()\n";
}

void State::CheckForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		bQuit = true;
	}
}
