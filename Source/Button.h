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

	sf::Color idle_text_color;
	sf::Color hover_text_color;
	sf::Color pressed_text_color;

	sf::Clock clock;

	STATES    STATE = STATES::BTN_IDLE;
public:
	Button(
		float x,
		float y, 
		float widht, 
		float height,
		string  text,
		sf::Font* font,
		sf::Color idle_text_color   = sf::Color(75, 75, 75, 255),		  //dark  grey
		sf::Color hover_text_color  = sf::Color(145, 145, 145, 255),      //light grey
		sf::Color active_text_color = sf::Color(150, 0, 0, 255),		  //dark  red
		sf::Color idle_color   = sf::Color(75,  75,  75,  0),   //dark  grey
		sf::Color hover_color  = sf::Color(145, 145, 145, 0),   //light grey
		sf::Color active_color = sf::Color(150, 0,   0,   0)    //dark  red
	);

	virtual ~Button();

	void Update(sf::Vector2f mouse_pos, const float& frame_time);
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

