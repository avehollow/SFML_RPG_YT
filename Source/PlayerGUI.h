#pragma once


class PlayerGUI
{
public:
	PlayerGUI(class Player* p, sf::RenderWindow* window);
	~PlayerGUI();

	void Update(const float& frame_time);
	void Render(sf::RenderWindow* window);


private:
	class Player* player;
	
	sf::RectangleShape hp_bar_back;
	sf::RectangleShape hp_bar_front;
	sf::Vector2f	   size_hp_bar;




	sf::Font font;
	sf::Text text;
};

