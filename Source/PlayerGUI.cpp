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
	// Dzia³a poprawnie tylko brakuje aktualizacji po zmianie okna (patrz w tym pliku funkcje Render() a w niej Adjust())
	size_hp_bar = sf::Vector2f(0.400f * window->getSize().y, 0.01f * window->getSize().x);
	hp_bar_back.setSize(size_hp_bar);

	hp_bar_back.setFillColor(sf::Color(50,50,50,150));
	hp_bar_back.setPosition(window->getSize().x * 0.02f, window->getSize().y * 0.02f);


	hp_bar_front.setSize(hp_bar_back.getSize());
	hp_bar_front.setFillColor(sf::Color(255,0,0,150));
	hp_bar_front.setPosition(hp_bar_back.getPosition());

	hp_bar_text.setFont(font);
	hp_bar_text.setFillColor(sf::Color::Black);

	std::string string_hp_bar = to_string(player->hp_current()) + " / " + to_string(player->hp_max());
	hp_bar_text.setString(string_hp_bar);
	hp_bar_text.setPosition(size_hp_bar.x / 2, size_hp_bar.y);
	hp_bar_text.setScale(0.6, 0.6);
	hp_bar_text.setStyle(sf::Text::Bold);
		
		
		
	//HLOG NEED BETTER SOLTUION
	size_exp_bar = sf::Vector2f(0.400f * window->getSize().y, 0.01f * window->getSize().x);
	exp_bar_back.setSize(size_exp_bar);

	exp_bar_back.setFillColor(sf::Color(50,50,50,150));
	exp_bar_back.setPosition(window->getSize().x * 0.02f, window->getSize().y * 0.05f);


	exp_bar_front.setSize(exp_bar_back.getSize());
	//#FFCC00
	exp_bar_front.setFillColor(sf::Color(255,204,0,150));
	exp_bar_front.setPosition(exp_bar_back.getPosition());

	exp_bar_text.setFont(font);
	exp_bar_text.setFillColor(sf::Color::Black);

	std::string string_exp_bar = to_string(player->experience()) + " / " + to_string(player->exp_to_next_level());
	exp_bar_text.setString(string_exp_bar);
	exp_bar_text.setPosition(size_exp_bar.x / 2, exp_bar_back.getPosition().y);
	exp_bar_text.setScale(0.6, 0.6);
	exp_bar_text.setStyle(sf::Text::Bold);
}


PlayerGUI::~PlayerGUI()
{

}

void PlayerGUI::Update(const float& frame_time)
{
	hp_bar_front.setScale( 
		sf::Vector2f(
				((float)player->attribute_component->hp_current / (float)player->attribute_component->hp_max), 
				1)
	);


	std::ostringstream ss;
	ss << player->hp_current() << " / " <<player->hp_max();

	// to_string() is very expensive???. Especially placed here, this mean, into Update() function ???
	// to_string() use to convert simple int/double... to string?
	//std::string string_hp_bar = to_string(player->hp_current()) + " / " + to_string(player->hp_max());
	hp_bar_text.setString(ss.str());



	exp_bar_front.setScale(
		sf::Vector2f(
			(float)player->attribute_component->experience / (float)player->attribute_component->exp_to_next_level,
			1)
	);

	;
	ss.str("");
	ss << player->experience() << " / " << player->exp_to_next_level();
	exp_bar_text.setString(ss.str());

}

void PlayerGUI::Render(sf::RenderWindow* window)
{
	// AVE Struktura (Najpierw Planuj Potem Koduj!) projektu nie pozwala w wygodny sposób aktualizowaæ rozmiaru interfejsu gracza w zale¿noœci od rozmiaru okna
	// W zwi¹zku z czym funkcja Adjust() jest wywo³ywana w tym miejscu (co jest niewskazane !)
	this->Adjust(window);
	
	
	window->draw(hp_bar_back);
	window->draw(hp_bar_front);
	window->draw(hp_bar_text);

	window->draw(exp_bar_back);
	window->draw(exp_bar_front);
	window->draw(exp_bar_text);
}

void PlayerGUI::Adjust(sf::RenderWindow* window)
{
	size_hp_bar = sf::Vector2f(0.400f * window->getSize().y, 0.01f * window->getSize().x);
	hp_bar_back.setSize(size_hp_bar);
	hp_bar_back.setPosition(window->getSize().x * 0.02f, window->getSize().y * 0.02f);


	hp_bar_front.setSize(hp_bar_back.getSize());
	hp_bar_front.setPosition(hp_bar_back.getPosition());


	hp_bar_text.setPosition(size_hp_bar.x / 2, size_hp_bar.y);


	//HLOG NEED BETTER SOLTUION
	size_exp_bar = sf::Vector2f(0.400f * window->getSize().y, 0.01f * window->getSize().x);
	exp_bar_back.setSize(size_exp_bar);
	exp_bar_back.setPosition(window->getSize().x * 0.02f, window->getSize().y * 0.05f);


	exp_bar_front.setSize(exp_bar_back.getSize());
	exp_bar_front.setPosition(exp_bar_back.getPosition());


	exp_bar_text.setPosition(size_exp_bar.x / 2, exp_bar_back.getPosition().y);
}
