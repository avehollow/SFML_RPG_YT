#pragma once
#include "State.h"
#include "Button.h"

class PauseState
{
private:
	sf::Font& font;
	sf::Text  text;

	sf::RectangleShape background;
	sf::RectangleShape container;

	map<string, unique_ptr<Button>> buttons;
public:
	PauseState(sf::RenderWindow* window, sf::Font& font);
	virtual ~PauseState();


	decltype(buttons)& GetButtons() {
		return buttons;
	}

	bool IsButtonPressed(std::string_view key);
	void AddButton(std::string_view key, float rel_x, float rel_y, std::string_view text);

	void Update(sf::Vector2f mos_pos, const float& frame_time); 
	void Render(sf::RenderWindow* target = nullptr);
};

