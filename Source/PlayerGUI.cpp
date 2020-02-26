#include "pch.h"
#include "PlayerGUI.h"
#include "Player.h"

PlayerGUI::PlayerGUI(Player* p, sf::RenderWindow* window)
{
	player = p;
	font.loadFromFile("Data/Fonts/Dosis-Light.ttf");

	// Calculate the size of the bars base on the size of window and
	// Calculate the position of the bars base on the position of the window 
	//HLOG NEED BETTER SOLTUION
	size_hp_bar = sf::Vector2f(0.400f * window->getSize().y, 0.01f * window->getSize().x);
	hp_bar_back.setSize(size_hp_bar);

	hp_bar_back.setFillColor(sf::Color(50,50,50,150));
	hp_bar_back.setPosition(window->getSize().x * 0.02f, window->getSize().y * 0.02f);


	hp_bar_front.setSize(hp_bar_back.getSize());
	hp_bar_front.setFillColor(sf::Color(255,0,0,150));
	hp_bar_front.setPosition(hp_bar_back.getPosition());
}

PlayerGUI::~PlayerGUI()
{

}

void PlayerGUI::Update(const float& frame_time)
{
	hp_bar_front.setSize( 
		sf::Vector2f(
				size_hp_bar.x*((float)player->attribute_component->hp_current / (float)player->attribute_component->hp_max), 
				size_hp_bar.y)
	);
}

void PlayerGUI::Render(sf::RenderWindow* window)
{
	window->draw(hp_bar_back);
	window->draw(hp_bar_front);
}
