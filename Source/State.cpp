#include "State.h"

State::State(shared_ptr<sf::RenderTarget> target, std::map<std::string, int>* supported_keys)
{
	this->window		 = target;
	this->supported_keys = supported_keys;
}

State::~State()
{
	std::cout << "Destructor State::~State()\n";
}

void State::CheckForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("QUIT"))))
	{
		bQuit = true;
	}
}
