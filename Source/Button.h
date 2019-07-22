#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>

using std::string;


class Button
{
	enum class STATES : uint8_t
	{
		BTN_IDLE    = 0,
		BTN_PRESSED = 1,
		BTN_HOVER   = 2
	};



private:
	sf::RectangleShape shape;
	sf::Text  text;
	sf::Font* font = nullptr;

	sf::Color idle_color;
	sf::Color hover_color;
	sf::Color pressed_color;

	STATES    STATE = STATES::BTN_IDLE;
public:
	Button(
		float x,
		float y, 
		float widht, 
		float height,
		string  text,
		sf::Font* font,
		sf::Color idle_color   = sf::Color::Blue,
		sf::Color hover_color  = sf::Color::Green, 
		sf::Color active_color = sf::Color::Red
	);

	virtual ~Button();

	void Update(sf::Vector2f mouse_pos);
	void Render(sf::RenderWindow* window);


	const bool IsPressed() const{
		return STATE == STATES::BTN_PRESSED ? true : false;
	}

	const bool IsHovered() const{
		return STATE == STATES::BTN_HOVER ?   true : false;
	}

	const bool IsIdle() const{
		return STATE == STATES::BTN_IDLE ?    true : false;
	}
};

