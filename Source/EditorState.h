#pragma once

#include "GameState.h"



class EditorState : public State
{
private:
	sf::RectangleShape background_s;
	sf::Texture		   background_t;

	sf::Font font_dosis;

	std::map<string, unique_ptr<gui::Button>> buttons;
	PauseState pause_menu;
	TileMap map;
	gui::TextureSelector texture_selector;


	sf::RectangleShape selected_tile;
	sf::Texture texture_sheet;

	sf::IntRect texture_rect;

	short layer          = 0;
	bool  bAddCollision  = false;
	bool  bShowCollision = false;

	sf::View view;
	float camera_speed = 8500;
public:
	EditorState(StateData* state_data);
	virtual ~EditorState();

	void InitButtons();
	void UpdateButtons(const float& frame_time);
	void RenderButtons(sf::RenderWindow* window = nullptr);

	void InitPauseMenu();
	void UpdatePauseMenuInput();


	void InitBackground();
	void InitFonts();
	void EndState()								 override;
	void InitKeybinds()							 override;
	void UpdateMousePos(sf::View* view = nullptr)override;

	void UpdateInput(const float& frame_time)		  override;
	void Update(const float& frame_time)			  override;
	void Render(sf::RenderWindow* window = nullptr)	  override;
};

