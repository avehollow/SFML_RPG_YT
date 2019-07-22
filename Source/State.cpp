#include "State.h"

State::State(weak_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys)
{
	this->window		 = window.lock();
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

void State::UpdateMousePos()
{
	mouse_pos_screen = sf::Mouse::getPosition();
	mouse_pos_window = sf::Mouse::getPosition(*window);
	mouse_pos_view   = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	std::cout << "Mouse_pos_screen  X: " << mouse_pos_screen.x <<"  Y: "<< mouse_pos_screen.y <<"\n";
	std::cout << "Mouse_pos_window  X: " << mouse_pos_window.x <<"  Y: "<< mouse_pos_window.y <<"\n";
	std::cout << "Mouse_pos_view    X: " << mouse_pos_view.x   <<"  Y: "<< mouse_pos_view.y;
	system("cls");
}
