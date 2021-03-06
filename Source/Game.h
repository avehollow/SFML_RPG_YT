#pragma once

#include "MainMenu.h"

// ImGui has been "removed" from project because of problem with precompiled headers
// However the files still exist in the project directory / However - jednak/mimo wszystko
//#include "imgui/imgui.h"
//#include "imgui-sfml/imgui-SFML.h"

using UINT = unsigned int;

class Game
{
public:
	Game();
	virtual ~Game();

	void Update();
	void Render();
	void Run();
	void UpdateSFMLEvents();
public:

private:
	void InitMainWindow();
	void InitStates();
	void InitKeys();
	void CalcFrameTime();
	void EndApplication();

private:
	std::shared_ptr<sf::RenderWindow> main_window;
	sf::Event						  sfEvent{};

	std::wstring					  window_title = L"SFML_RPG_YT";

	sf::Clock						  frame_clock;
	float							  frame_time = 0.0f;

	std::stack<unique_ptr<State>>	  states;

	std::map<std::string, int>		  supported_keys;

	StateData state_data;
};

