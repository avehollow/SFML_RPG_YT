#pragma once


class PlayerGUI
{
public:
	PlayerGUI(class Player* p, sf::RenderWindow* window);
	~PlayerGUI();

	void Update(const float& frame_time);
	void Render(sf::RenderWindow* window);
	void Adjust(sf::RenderWindow* window);


private:
	class Player* player;
	
	sf::Text		   hp_bar_text;
	sf::RectangleShape hp_bar_back;
	sf::RectangleShape hp_bar_front;
	sf::Vector2f	   size_hp_bar;
	
	
	sf::Text		   exp_bar_text;
	sf::RectangleShape exp_bar_back;
	sf::RectangleShape exp_bar_front;
	sf::Vector2f	   size_exp_bar;




	sf::Font font;
};

