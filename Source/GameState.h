#pragma once

#include "State.h"

class GameState : public State
{
private:
	shared_ptr<Player> player;

public:
	GameState(weak_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys, std::stack<unique_ptr<State>>* states);
	virtual ~GameState();

	void InitTextures();
	void InitSprites();


	void EndState()								 override;
	void InitKeybinds()							 override;
	void UpdateMousePos()						 override;

	void UpdateInput(const float& frame_time)		  override;
	void Update(const float& frame_time)			  override;
	void Render(sf::RenderWindow* target = nullptr)	  override;
};

