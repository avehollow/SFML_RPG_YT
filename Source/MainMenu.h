#pragma once
#include "SettingsState.h"

class MainMenu : public State
{
private:
	sf::RectangleShape background_s;
	sf::Texture		   background_t;

	sf::RectangleShape blackarea;

	std::map<string, unique_ptr<gui::Button>> buttons;
public:
	MainMenu(StateData* state_data);
	virtual ~MainMenu();

	void InitButtons();
	void UpdateButtons(const float& frame_time);
	void RenderButtons(sf::RenderWindow* window = nullptr);


	void InitBackground();
	void InitFonts();
	void EndState()								      override;
	void InitKeybinds()							      override;
	void UpdateMousePos(sf::View* view = nullptr)	  override;

	void UpdateInput(const float& frame_time)		  override;
	void Update(const float& frame_time)			  override;
	void Render(sf::RenderWindow* window = nullptr)	  override;
};

