#pragma once

#include "PauseState.h"
#include "TileMap.h"

class GameState : public State
{
private:
	sf::View view;
	sf::RenderTexture render_texture;
	sf::Sprite render_all_world;

	PauseState pause_menu;
	shared_ptr<Player> player;
	// Foward declaration works :)
	shared_ptr < class PlayerGUI > playerGUI;

	sf::Texture texture_sheet;
	TileMap map;

public:
	GameState(StateData* state_data);
	virtual ~GameState();

	void InitTextures();
	void InitSprites();
	void InitView();
	
	void InitPauseMenu();
	void UpdatePauseMenuInput();
	void UpdateView();


	void EndState()									  override;
	void InitKeybinds()								  override;
	void UpdateMousePos(sf::View* view = nullptr)	  override;

	void UpdateInput(const float& frame_time)		  override;
	void Update(const float& frame_time)			  override;
	void Render(sf::RenderWindow* window = nullptr)	  override;
};

