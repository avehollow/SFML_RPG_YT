#pragma once

#include "State.h"

class GameState : public State
{
private:
	Entity player;

public:
	GameState(weak_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys);
	virtual ~GameState();

	void EndState()       override;
	void CheckForQuit()   override;
	void InitKeybinds()   override;
	void UpdateMousePos() override;

	void UpdateInput(const float& frame_time)		  override;
	void Update(const float& frame_time)			  override;
	void Render(sf::RenderWindow* target = nullptr)	  override;
};

