#include "Game.h"


Game::Game()
{
}

Game::~Game()
{
}

void Game::Update()
{
	this->UpdateSFMLEvents();
}

void Game::Render()
{
	main_window->clear();

	main_window->display();
}

void Game::Run()
{
	this->InitMainWindow();

	while (main_window->isOpen())
	{
		this->CalcFrameTime();
		this->Update();
		this->Render();
	}
}

void Game::UpdateSFMLEvents()
{
	while (main_window->pollEvent(sfEvent))
	{
		if (sfEvent.type == sf::Event::Closed)
			main_window->close();

	}
}

void Game::InitMainWindow()
{
	main_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WIDTH_1280, HEIGHT_800), window_title.c_str(), sf::Style::Titlebar | sf::Style::Close);
	main_window->setFramerateLimit(120);
	main_window->setVerticalSyncEnabled(false);
}

void Game::CalcFrameTime()
{
	frame_time = frame_clock.restart().asSeconds();
	system("cls");
	std::cout << frame_time << "\n";
}
