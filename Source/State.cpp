#include "State.h"

State::State(weak_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys, std::stack<unique_ptr<State>>* states)
{
	this->window = window.lock();
	this->supported_keys = supported_keys;
	this->states = states;
}

State::~State()
{
	std::cout << "Destructor State::~State()\n";
}

void State::UpdateMousePos()
{
	mouse_pos_screen = sf::Mouse::getPosition();
	mouse_pos_window = sf::Mouse::getPosition(*window);
	mouse_pos_view   = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

}
