#pragma once
#include "SettingsState.h"

class MainMenu : public State
{
private:
	sf::RectangleShape background_s;
	sf::Texture		   background_t;

	std::map<string, unique_ptr<Button>> buttons;
public:
	MainMenu(weak_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys, std::stack<unique_ptr<State>>* states);
	virtual ~MainMenu();

	void InitButtons();
	void UpdateButtons(const float& frame_time);
	void RenderButtons(sf::RenderWindow* window = nullptr);


	void InitBackground();
	void InitFonts();
	void EndState()								 override;
	void InitKeybinds()							 override;
	void UpdateMousePos()						 override;

	void UpdateInput(const float& frame_time)		  override;
	void Update(const float& frame_time)			  override;
	void Render(sf::RenderWindow* window = nullptr)	  override;
};

