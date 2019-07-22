#pragma once
#include "GameState.h"
#include "Button.h"

class MainMenu : public State
{
private:
	sf::RectangleShape background;

	sf::Font font_dosis;

	unique_ptr<Button> button;
public:
	MainMenu(weak_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys);
	virtual ~MainMenu();

	void InitFonts();
	void EndState()       override;
	void CheckForQuit()   override;
	void InitKeybinds()   override;
	void UpdateMousePos() override;

	void UpdateInput(const float& frame_time)		  override;
	void Update(const float& frame_time)			  override;
	void Render(sf::RenderWindow* window = nullptr)	  override;
};

