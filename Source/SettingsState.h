#pragma once
#include "EditorState.h"

class SettingsState : public State
{
	struct Settings
	{
		union
		{
			std::array<int, 4> parm;
			struct
			{
				int  width;			// = 1920;
				int  height;		// = 1080;
				int  bpp;			// = 32;
				int  bFullScreen;	// = 1;
			};
		};
	};

private:
	sf::RectangleShape background_s;
	sf::Texture		   background_t;

	std::map<string, unique_ptr<gui::Button>>   buttons;
	std::map<string, shared_ptr<gui::DropList>> drop_lists;

	vector<sf::VideoMode> video_modes;

	Settings current_setting;
	
public:
	SettingsState(StateData* state_data);
	virtual ~SettingsState();

	void InitBackground();
	void InitFonts();
	void InitGui();

	void UpdateGui(const float& frame_time);
	void RenderGui(sf::RenderWindow* window = nullptr);


	// Inherited via State // via - przez/za poœrednictwem
	virtual void EndState() override;
	virtual void InitKeybinds() override;
	virtual void UpdateInput(const float& frame_time) override;
	virtual void Update(const float& frame_time) override;
	virtual void Render(sf::RenderWindow* target = nullptr) override;
};

