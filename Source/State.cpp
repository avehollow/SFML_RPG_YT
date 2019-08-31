#include "State.h"

State::State(shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys, std::stack<unique_ptr<State>>* states)
{
	this->window = window;
	this->supported_keys = supported_keys;
	this->states = states;

	if (!font_dosis.loadFromFile("Data/Fonts/Dosis-Light.ttf"))
	{
		std::cout << "\nError! MainMenu::InitFonts()! Dosis\n";
		throw "Error! MainMenu::InitFonts()! Dosis";
	}
}

State::~State()
{
	std::cout << "Destructor State::~State()\n";
}

bool State::KeyTime()
{
	if (key_time >= key_time_max)
	{
		key_time = 0.0f;
		return true;
	}
	return false;
}

void State::UpdateKeyTime(const float& frame_time)
{
	key_time += frame_time;
}

void State::UpdateMousePos()
{
	mouse_pos_screen = sf::Mouse::getPosition();
	mouse_pos_window = sf::Mouse::getPosition(*window);
	mouse_pos_view   = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

}
