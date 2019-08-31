#pragma once
#include "Player.h"

class State
{
protected:
	stack<unique_ptr<State>>*	    states; // Only acces pointer to a normal variable (nodynamic)
	shared_ptr<sf::RenderWindow>	window;

	map<string, int>*				supported_keys = nullptr;
	map<string, int>				current_keybinds;
	map<string, sf::Texture>        textures;
	map<string, sf::Sprite>         sprites;
	
	sf::Vector2i mouse_pos_screen;
	sf::Vector2i mouse_pos_window;
	sf::Vector2f mouse_pos_view;

	sf::Font font_dosis;



	float key_time     = 0.0f;
	float key_time_max = 0.1f;


	bool bQuit  = false;

public: 
	bool bPause = false;

public:
	State(shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys, std::stack<unique_ptr<State>>* states);
	virtual ~State();

	const bool& GetQuitFlag()const {
		return bQuit;
	};

	virtual bool KeyTime();
	virtual void UpdateKeyTime(const float& frame_time);
	virtual void UpdateMousePos();
	virtual void EndState()									  = 0;
	virtual void InitKeybinds()								  = 0;
	virtual void UpdateInput(const float& frame_time)		  = 0;
	virtual void Update(const float& frame_time)			  = 0;
	virtual void Render(sf::RenderWindow* target = nullptr )  = 0;
};

