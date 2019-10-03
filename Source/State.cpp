#include "pch.h"
#include "State.h"

State::State(StateData* state_data)
{
	this->state_data     = state_data;
	this->window         = state_data->window;
	this->supported_keys = state_data->supported_keys;
	this->states         = state_data->states;
	this->gird_size      = state_data->tile_size;

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

void State::UpdateMousePos(sf::View* view)
{
	mouse_pos_screen = sf::Mouse::getPosition();
	mouse_pos_window = sf::Mouse::getPosition(*window);

	if (view)
	{
		window->setView(*view);
	}
	else
	{
		window->setView(window->getDefaultView());
	}

	mouse_pos_view.x = window->mapPixelToCoords(sf::Mouse::getPosition(*window)).x;
	mouse_pos_view.y = window->mapPixelToCoords(sf::Mouse::getPosition(*window)).y;


	mouse_pos_grid.x = ((int)mouse_pos_view.x) / state_data->tile_size;
	mouse_pos_grid.y = ((int)mouse_pos_view.y) / state_data->tile_size;

	//std::cout << "X:" << mouse_pos_grid.x << "  Y: " << mouse_pos_grid.y << "\n";

}
