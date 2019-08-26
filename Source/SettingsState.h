#pragma once
#include "EditorState.h"

class SettingsState : public State
{
private:
	sf::RectangleShape background_s;
	sf::Texture		   background_t;

	std::map<string, unique_ptr<gui::Button>> buttons;

	shared_ptr<gui::DropList> dl;
public:
	SettingsState(weak_ptr<sf::RenderWindow> window, std::map<std::string, int>* supported_keys, std::stack<unique_ptr<State>>* states);
	virtual ~SettingsState();

	void InitBackground();
	void InitFonts();
	void InitButtons();

	void UpdateButtons(const float& frame_time);
	void RenderButtons(sf::RenderWindow* window = nullptr);


	// Inherited via State // via - przez/za poœrednictwem
	virtual void EndState() override;
	virtual void InitKeybinds() override;
	virtual void UpdateInput(const float& frame_time) override;
	virtual void Update(const float& frame_time) override;
	virtual void Render(sf::RenderWindow* target = nullptr) override;
};

