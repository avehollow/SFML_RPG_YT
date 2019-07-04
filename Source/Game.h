#pragma once

#include "imgui/imgui.h"
#include "imgui-sfml/imgui-SFML.h"
#include "SFML/Graphics.hpp"

#include <iostream>
#include <memory>
#include <string>

using UINT = unsigned int;

constexpr UINT WIDTH_1920  = 1920;
constexpr UINT HEIGHT_1080 = 1080;

constexpr UINT WIDTH_1280  = 1280;
constexpr UINT HEIGHT_800  = 800;


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
	void CalcFrameTime();

private:
	std::unique_ptr<sf::RenderWindow> main_window;
	sf::Event sfEvent;

	std::wstring window_title = L"SFML_RPG_YT";

	sf::Clock frame_clock;
	float frame_time = 0.0;
};

