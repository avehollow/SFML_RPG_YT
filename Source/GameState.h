#pragma once

#include "PauseState.h"
#include "TileMap.h"

class GameState : public State
{
private:
	PauseState pause_menu;
	shared_ptr<Player> player;

	TileMap map;

public:
	GameState(StateData* state_data);
	virtual ~GameState();

	void InitTextures();
	void InitSprites();
	
	void InitPauseMenu();
	void UpdatePauseMenuInput();


	void EndState()			override;
	void InitKeybinds()		override;
	void UpdateMousePos()	override;

	void UpdateInput(const float& frame_time)		  override;
	void Update(const float& frame_time)			  override;
	void Render(sf::RenderWindow* target = nullptr)	  override;
};

