#pragma once

#include "GameState.h"

class EditorState : public State
{
private:
	sf::RectangleShape background_s;
	sf::Texture		   background_t;

	sf::Font font_dosis;

	std::map<string, unique_ptr<gui::Button>> buttons;
public:
	EditorState(weak_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys, std::stack<unique_ptr<State>>* states);
	virtual ~EditorState();

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

