#include "pch.h"
#include "Game.h"


Game::Game()
	: state_data({ 51,51,100.0f,main_window,&supported_keys,&states }) //AVE Klasa agregat
{

}

Game::~Game()
{
	
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
	this->state_data.window = main_window;

	// Init Keys must be before InitStates()
	this->InitKeys();
	this->InitStates();

	while (main_window->isOpen())
	{
		if (main_window->hasFocus())
		{
			this->CalcFrameTime();
			this->Update();
		}

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
	sf::ContextSettings window_settings;
	// Bad idea
	//window_settings.antialiasingLevel = 1;

	std::ifstream ifs("Config/settings.ini");
	int width	    = 1920, 
	    height	    = 1080, 
		bpp		    = 32  ,
		bFullScreen = 1;

	if (ifs.is_open())
	{
		std::string setting_name;


		ifs >> setting_name >> width
			>> setting_name >> height
			>> setting_name >> bpp
			>> setting_name >> bFullScreen;
	}
	ifs.close();

	if (!bFullScreen)
	{
		main_window = make_shared<sf::RenderWindow>(
														sf::VideoMode(width, height, bpp),
														window_title.c_str(),
														sf::Style::Titlebar | sf::Style::Close
													);
	}
	else
	{
		main_window = make_shared<sf::RenderWindow>(
														sf::VideoMode(width, height, bpp),
														window_title.c_str(),
														sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen
													);

	}
	
	// AVE lock framerate 
	// Bad idea

	//HLOG SetFramerateLimit
     //main_window->setFramerateLimit(200);
	 //main_window->setVerticalSyncEnabled(false);
}

void Game::InitStates()
{
	//Before ->> STATE constructor have &weak_ptr as 1 parametr and we cant pass as argument a shared_ptr because shared is not can be ref to weak_ptr
	//weak_ptr<sf::RenderWindow> window = main_window;
	states.push(make_unique<MainMenu> (&state_data));
}

void Game::InitKeys()
{
	supported_keys.emplace("A",	 static_cast<int>(sf::Keyboard::Key::A));
	supported_keys.emplace("B",	 static_cast<int>(sf::Keyboard::Key::B));
	supported_keys.emplace("C",	 static_cast<int>(sf::Keyboard::Key::C));
	supported_keys.emplace("D",	 static_cast<int>(sf::Keyboard::Key::D));
	supported_keys.emplace("E",	 static_cast<int>(sf::Keyboard::Key::E));
	supported_keys.emplace("F",	 static_cast<int>(sf::Keyboard::Key::F));
	supported_keys.emplace("G",	 static_cast<int>(sf::Keyboard::Key::G));
	supported_keys.emplace("H",	 static_cast<int>(sf::Keyboard::Key::H));
	supported_keys.emplace("I",	 static_cast<int>(sf::Keyboard::Key::I));
	supported_keys.emplace("J",	 static_cast<int>(sf::Keyboard::Key::J));
	supported_keys.emplace("K",	 static_cast<int>(sf::Keyboard::Key::K));
	supported_keys.emplace("L",	 static_cast<int>(sf::Keyboard::Key::L));
	supported_keys.emplace("M",	 static_cast<int>(sf::Keyboard::Key::M));
	supported_keys.emplace("N",	 static_cast<int>(sf::Keyboard::Key::N));
	supported_keys.emplace("O",	 static_cast<int>(sf::Keyboard::Key::O));
	supported_keys.emplace("P",	 static_cast<int>(sf::Keyboard::Key::P));
	supported_keys.emplace("Q",	 static_cast<int>(sf::Keyboard::Key::Q));
	supported_keys.emplace("R",	 static_cast<int>(sf::Keyboard::Key::R));
	supported_keys.emplace("S",	 static_cast<int>(sf::Keyboard::Key::S));
	supported_keys.emplace("T",	 static_cast<int>(sf::Keyboard::Key::T));
	supported_keys.emplace("U",	 static_cast<int>(sf::Keyboard::Key::U));
	supported_keys.emplace("V",	 static_cast<int>(sf::Keyboard::Key::V));
	supported_keys.emplace("W",	 static_cast<int>(sf::Keyboard::Key::W));
	supported_keys.emplace("X",	 static_cast<int>(sf::Keyboard::Key::X));
	supported_keys.emplace("Y",	 static_cast<int>(sf::Keyboard::Key::Y));
	supported_keys.emplace("Z",	 static_cast<int>(sf::Keyboard::Key::Z));

	supported_keys.emplace("0",		static_cast<int>(sf::Keyboard::Key::Num0));
	supported_keys.emplace("1",		static_cast<int>(sf::Keyboard::Key::Num1));
	supported_keys.emplace("2",		static_cast<int>(sf::Keyboard::Key::Num2));
	supported_keys.emplace("3",		static_cast<int>(sf::Keyboard::Key::Num3));
	supported_keys.emplace("4",		static_cast<int>(sf::Keyboard::Key::Num4));
	supported_keys.emplace("5",		static_cast<int>(sf::Keyboard::Key::Num5));
	supported_keys.emplace("6",		static_cast<int>(sf::Keyboard::Key::Num6));
	supported_keys.emplace("7",		static_cast<int>(sf::Keyboard::Key::Num7));
	supported_keys.emplace("8",		static_cast<int>(sf::Keyboard::Key::Num8));
	supported_keys.emplace("9",		static_cast<int>(sf::Keyboard::Key::Num9));

	supported_keys.emplace("Escape",    static_cast<int>(sf::Keyboard::Key::Escape));
	supported_keys.emplace("LControl",  static_cast<int>(sf::Keyboard::Key::LControl));
	supported_keys.emplace("LShift",    static_cast<int>(sf::Keyboard::Key::LShift));
	supported_keys.emplace("LAlt",      static_cast<int>(sf::Keyboard::Key::LAlt));
	supported_keys.emplace("LSystem",   static_cast<int>(sf::Keyboard::Key::LSystem));
	supported_keys.emplace("RControl",  static_cast<int>(sf::Keyboard::Key::RControl));
	supported_keys.emplace("RShift",    static_cast<int>(sf::Keyboard::Key::RShift));
	supported_keys.emplace("RAlt",      static_cast<int>(sf::Keyboard::Key::RAlt));
	supported_keys.emplace("RSystem",   static_cast<int>(sf::Keyboard::Key::RSystem));
	supported_keys.emplace("Tilde",     static_cast<int>(sf::Keyboard::Key::Tilde));
	supported_keys.emplace("Space",     static_cast<int>(sf::Keyboard::Key::Space));
	supported_keys.emplace("Enter",     static_cast<int>(sf::Keyboard::Key::Enter));
	supported_keys.emplace("Backspace", static_cast<int>(sf::Keyboard::Key::Backspace));
	supported_keys.emplace("Tab",       static_cast<int>(sf::Keyboard::Key::Tab));
	//Arrows
	supported_keys.emplace("Left",		static_cast<int>(sf::Keyboard::Key::Left));
	supported_keys.emplace("Right",		static_cast<int>(sf::Keyboard::Key::Right));
	supported_keys.emplace("Up",		static_cast<int>(sf::Keyboard::Key::Up));
	supported_keys.emplace("Down",      static_cast<int>(sf::Keyboard::Key::Down));

	supported_keys.emplace("F1",		static_cast<int>(sf::Keyboard::Key::F1));
	supported_keys.emplace("F2",		static_cast<int>(sf::Keyboard::Key::F2));
	supported_keys.emplace("F3",		static_cast<int>(sf::Keyboard::Key::F3));
	supported_keys.emplace("F4",		static_cast<int>(sf::Keyboard::Key::F4));
	supported_keys.emplace("F5",		static_cast<int>(sf::Keyboard::Key::F5));
	supported_keys.emplace("F6",		static_cast<int>(sf::Keyboard::Key::F6));
	supported_keys.emplace("F7",		static_cast<int>(sf::Keyboard::Key::F7));
	supported_keys.emplace("F8",		static_cast<int>(sf::Keyboard::Key::F8));
	supported_keys.emplace("F9",		static_cast<int>(sf::Keyboard::Key::F9));

}

void Game::CalcFrameTime()
{
	frame_time = frame_clock.restart().asSeconds();
	
	static double time = 0;
	time += frame_time;
	static int fps = 0;
	++fps;
	
	if (time >= 1.0)
	{
		fps = 0;
		time = 0;
		std::wstring title = window_title + L"   FPS: " + std::to_wstring(1.0f / frame_time) + L"      Frame_Time = " + std::to_wstring(frame_time);
		main_window->setTitle(title);
	}
	
	
}

void Game::EndApplication()
{
}
