#include "Game.h"


Game::Game()
{
}

Game::~Game()
{
	while (!states.empty())
	{
		states.pop();
	}
}

void Game::Update()
{
	this->UpdateSFMLEvents();
	
	if (!states.empty()) 
	{
		states.top()->Update(frame_time);

		if (states.top()->GetQuitFlag())
		{
			states.top()->EndState();
			states.pop();
		}
	}
	else
	{
		this->EndApplication();
		main_window->close();
	}
}

void Game::Render()
{
	main_window->clear();

	if (!states.empty())
	{
		states.top()->Render(main_window.get());
	}

	main_window->display();
}

void Game::Run()
{
	this->InitMainWindow();
	this->InitKeys();
	this->InitStates();

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
	main_window = make_unique<sf::RenderWindow>(sf::VideoMode(WIDTH_1280, HEIGHT_800), window_title.c_str(), sf::Style::Titlebar | sf::Style::Close);
	main_window->setFramerateLimit(120);
	main_window->setVerticalSyncEnabled(false);
}

void Game::InitStates()
{
	states.push(make_unique<GameState>(main_window.get(), &supported_keys));
}

void Game::InitKeys()
{
	supported_keys.emplace("ESCAPE", static_cast<int>(sf::Keyboard::Key::Escape));
	supported_keys.emplace("A", static_cast<int>(sf::Keyboard::Key::A));
	supported_keys.emplace("D", static_cast<int>(sf::Keyboard::Key::D));
	supported_keys.emplace("W", static_cast<int>(sf::Keyboard::Key::W));
	supported_keys.emplace("S", static_cast<int>(sf::Keyboard::Key::S));
}

void Game::CalcFrameTime()
{
	//HACK freak way/method to calculate fps
	frame_time = frame_clock.restart().asSeconds();
	std::wstring title = window_title + L"   FPS: " + std::to_wstring(1.0f/frame_time) + L"      Frame_Time = " + std::to_wstring(frame_time);
	main_window->setTitle(title);
}

void Game::EndApplication()
{
}
