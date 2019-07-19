#pragma once

#include "State.h"

class GameState : public State
{
private:
	Entity player;

public:
	GameState(shared_ptr<sf::RenderTarget> target, std::map<std::string, int>* supported_keys);
	virtual ~GameState();

	void EndState()     override;
	void CheckForQuit() override;
	void InitKeybinds() override;

	void UpdateInput(const float& frame_time)		  override;
	void Update(const float& frame_time)			  override;
	void Render(sf::RenderTarget* target = nullptr)	  override;
};

