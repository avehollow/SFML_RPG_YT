#include "pch.h"
#include "GameState.h"
#include "SettingsState.h"
#include "PlayerGUI.h"

//HACK Why i sent suported_keys to State.h if i in this place fill map keybinds? After this i dont need sent supported_keys to State
GameState::GameState(StateData* state_data)
	: State(state_data), pause_menu(window.get(), font_dosis)
	, map(nullptr)
{
	this->InitKeybinds();
	this->InitTextures();

	this->InitSprites();
	player    = make_shared<Player>(20, 20, &sprites["PLAYER"], &textures["PLAYER"]);
	playerGUI = make_shared<PlayerGUI>(player.get(), window.get());

	this->InitPauseMenu();

	texture_sheet.loadFromFile("Resource/Image/Sprites/Tiles/tilesheet1.png");
	map.SetTextureSheet(&texture_sheet);
	map.LoadFromFile();

	this->InitView();

	//playerGUI->Adjust();
}

GameState::~GameState()
{
	std::cout << "\nDestructor GameState::~GameState()\n";
}

void GameState::InitTextures()
{
	textures["PLAYER"].loadFromFile("Resource/Image/Sprites/Player/PLAYER_SHEET.png");
}

void GameState::InitSprites()
{
	sprites["PLAYER"].setTexture(textures["PLAYER"]);
	// Works. Create new sprite!
	//sprites["PLAYER1"].setTexture(textures["PLAYER"]);
	//sprites["PLAYER2"].setTexture(textures["PLAYER"]);
	std::cout <<"\n\nCount sprites: "<< sprites.size();
}

void GameState::InitView()
{
	view.setSize(sf::Vector2f(window->getSize()));
	view.setCenter(
				   window->getSize().x / 2.0f,
				   window->getSize().y / 2.0f
	);
	    std::cout << "\n Rozmiar okna X: " << window->getSize().x;
		std::cout << "\n Rozmiar okna Y: " << window->getSize().y;
}



void GameState::InitPauseMenu()
{
	pause_menu.AddButton("Resume",  250.0f,                             "Resume");
	pause_menu.AddButton("Options", window.get()->getSize().y - 500.0f, "Options"  );
	pause_menu.AddButton("Quit",    window.get()->getSize().y - 250.0f, "Quit"  );
}

void GameState::UpdatePauseMenuInput()
{
	if (pause_menu.IsButtonPressed("Quit"))     bQuit = true;

	if (pause_menu.IsButtonPressed("Resume"))	bPause = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("QUIT"))) && KeyTime())
	{
		if (bPause) bPause = false;
	}

	if (pause_menu.IsButtonPressed("Options"))
	{
		states->push(make_unique<SettingsState>(state_data));
	}
	
}

void GameState::UpdateView()
{
	// AVE Use intengers values to move view because using float causes flickering tile textures!
	// AVE Very nice mechanic!!
	// The player pawn moves the camera, but also the mouse can move the camera a little 

	// Kamera pod��a za pozycj� gracza
	// Chcemy aby kamere r�wnie� nieznacznie porusza�a myszka (ruch myszk�)
	// W tym celu do pozycji gracza dodajemy pozycje myszki z tym �e
	// Domy�lna pozycja myszy to lewy g�rny r�g czyli punkt (0,0)
	// Przesuwaj�c j� np. na �rodek ekranu na posta� gracza otrzymamy wsp�rz�dne myszki r�wne (windows->getSize().x, windows->getSize().y)  czyli np. (960,540)
	// Je�eli dodamy do wsp�rz�dnych gracza wektor (960,540) to kamera przesunie si� o ten wektor (prawdopodobnie gracza nawet wida� nie bedzie).
	// Co jest niew�a�ciwe poniewa� chcemy aby gracz by� na �rodku i mysz r�wnie� 
	// Dlatego odejmujemy po�owe rozmiar�w okna od pozycji myszy co skutuje tym �e
	// !! Naje�dzaj�c myszk� na gracza, mysz a raczej jej pozycja jest na �rodku okna !!
	// I oto nam chodzi�o
	// Kolejno dzielimy otrzyman� w ten sp�b pozycje myszy przez 5.0f aby ograniczy� ruch mysz�
	// Je�eli chcemy aby myszka bardziej wp�ywa�a na kamera b�d� mniej to edytujemy warto�� / 5.0f
	// Musz� by� rzutowania na float!!!
	view.setCenter(
		(player->GetPosition().x + (((float)this->mouse_pos_window.x - (float)window->getSize().x / 2) / 5.0f)), 
		(player->GetPosition().y + (((float)this->mouse_pos_window.y - (float)window->getSize().y / 2) / 5.0f)));
}

void GameState::EndState()
{

}


void GameState::InitKeybinds()
{
	std::ifstream ifs("Config/keybinds.ini");
	if (ifs.is_open())
	{
		std::string name_action;
		int key;
		while (ifs >> name_action >> key)
		{
			current_keybinds[name_action] = key;
		}
	}
	else
	{
		//HACK MessageBox ?
	}
	ifs.close();
}

void GameState::UpdateMousePos(sf::View* view)
{
	State::UpdateMousePos(view);
}

void GameState::UpdateInput(const float& frame_time)
{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("MOVE_LEFT"))))
		{
			this->player->move(frame_time, -1.0f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("MOVE_RIGHT"))))
		{
			this->player->move(frame_time, +1.0f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("MOVE_UP"))))
		{
			this->player->move(frame_time, 0.0f, -1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("MOVE_DOWN"))))
		{
			this->player->move(frame_time, 0.0f, +1.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(current_keybinds.at("QUIT"))) && KeyTime())
		{
			if (!bPause) bPause = true;
		}
}

void GameState::Update(const float& frame_time)
{
	this->UpdateMousePos(&view); 
	this->UpdateKeyTime(frame_time);

	if (bPause)
	{
		this->UpdatePauseMenuInput();
		pause_menu.Update(sf::Vector2f(mouse_pos_window), frame_time);
	}
	else
	{ 
		this->UpdateView();
		this->UpdateInput(frame_time);
		//AVE VERY IMPORTANT!!! Check collision before update player
		map.UpdateCollision(player.get(),frame_time);
		player->Update(frame_time);
		//HLOG In which situation playerGUI->update should be called ??;
		playerGUI->Update(frame_time);
	}
}

void GameState::Render(sf::RenderWindow* window)
{
	if (!window)
		return;
	
	window->setView(view);

	map.Render(window, player.get());
	//player->Render(target);

	// The player character is rendered by the map
	// Because some objects are placed above the player
	// i.e  1 layer --> grass 
	//		2 layer --> road , 
	//	    RENDER PLAYER 
	//	    3 layer --> tree

	// Render Player GUI
	window->setView(window->getDefaultView());
	playerGUI->Render(window);

	if (bPause)
	{
		window->setView(window->getDefaultView());
		pause_menu.Render(window);
	}
}
