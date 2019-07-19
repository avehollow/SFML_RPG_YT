#pragma once
#include "Entity.h"

class State
{
protected:
	// States dont need windows,
	shared_ptr<sf::RenderTarget>	window;

	std::map<string, int>*		    supported_keys = nullptr;
	std::map<string, int>		    current_keybinds;
	std::vector<sf::Texture>        textures;
	

	bool bQuit = false;

	virtual void InitKeybinds() = 0;

public:
	State(shared_ptr<sf::RenderTarget> target, std::map<std::string, int>* supported_keys);
	virtual ~State();

	const bool& GetQuitFlag()const {
		return bQuit;
	};

	virtual void CheckForQuit();

	virtual void EndState()									  = 0;

	virtual void UpdateInput(const float& frame_time)		  = 0;
	virtual void Update(const float& frame_time)			  = 0;
	virtual void Render(sf::RenderTarget* target = nullptr )  = 0;
};

