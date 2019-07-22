#pragma once
#include "Entity.h"

class State
{
protected:
	shared_ptr<sf::RenderWindow>	window;

	std::map<string, int>*		    supported_keys = nullptr;
	std::map<string, int>		    current_keybinds;
	std::vector<sf::Texture>        textures;
	
	sf::Vector2i mouse_pos_screen;
	sf::Vector2i mouse_pos_window;
	sf::Vector2f mouse_pos_view;



	bool bQuit = false;



public:
	State(weak_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys);
	virtual ~State();

	const bool& GetQuitFlag()const {
		return bQuit;
	};

	virtual void CheckForQuit();

	virtual void UpdateMousePos();
	virtual void EndState()									  = 0;
	virtual void InitKeybinds()								  = 0;
	virtual void UpdateInput(const float& frame_time)		  = 0;
	virtual void Update(const float& frame_time)			  = 0;
	virtual void Render(sf::RenderWindow* target = nullptr )  = 0;
};

