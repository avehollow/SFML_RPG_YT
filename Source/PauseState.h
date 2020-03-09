#pragma once
#include "State.h"
#include "Gui.h"

class PauseState
{
private:
	sf::Font& font;
	sf::Text  text;

	sf::RectangleShape background;
	sf::RectangleShape container;

	map<string, unique_ptr<gui::Button>> buttons;
public:
	PauseState(sf::RenderWindow* window, sf::Font& font);
	virtual ~PauseState();


	decltype(buttons)& GetButtons() {
		return buttons;
	}

	bool IsButtonPressed(std::string_view key);

	/* The pause menu has constant dimensions, this mean -> it is always in the center of the window
	*
	*	@param			float rel_y			Indicate_wskazywac the position of the button relative to the pause menu window
	*/
	void AddButton(std::string_view key, float rel_y, std::string_view text);

	void Update(sf::Vector2f mos_pos, const float& frame_time); 
	void Render(sf::RenderWindow* target = nullptr);
};

