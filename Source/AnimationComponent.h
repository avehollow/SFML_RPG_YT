#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <map>



//This pointer does not manage memory; Dont try to delete ! This pointer used only for access to data
#define ACCESS_POINTER 

class AnimationComponent
{
private:
	class Animation
	{
	public:
		ACCESS_POINTER sf::Texture* sheet  = nullptr;
		ACCESS_POINTER sf::Sprite*  sprite = nullptr;
		
		sf::IntRect start_pos;
		sf::IntRect end_pos;
		sf::IntRect curr_pos;

		sf::Clock	clock;

		float speed		= 0.0f;
		int   width     = 0.f;
		int   height    = 0.f;

	public:
		Animation(sf::Texture* sheet, int speed, int start_x, int start_y, int end_x, int end_y, int width, int height)
			: sheet(sheet)
			, speed(speed)
			, width(width)
			, height(height)
		{
			start_pos = sf::IntRect(start_x, start_y, width, height);
			end_pos   = sf::IntRect(end_x,   end_y,   width, height);
			curr_pos  = start_pos;

			sprite->setTexture(*sheet, true);
			sprite->setTextureRect(start_pos);
		}
		~Animation() = default;

		void Update(const float& frame_time)
		{
			// HACK * frame_time!
			if (clock.getElapsedTime().asSeconds() * frame_time > speed)
			{
				if (curr_pos != end_pos)
				{
					curr_pos.left += width;
				}
				else
				{
					curr_pos = start_pos;
				}


				clock.restart();
			}
		}

		// HACK Add function
		void Play() {};
		void Pause() {};
		void Reset() {};

	};// End class Animation

private:
	sf::Texture* sheet  = nullptr;
	sf::Sprite*  sprite = nullptr;
	std::map<std::string, Animation> animations;

public:
	AnimationComponent();
	virtual ~AnimationComponent();

	void AddAnimation(std::string_view key);
	
	void Update(const float& frame_time);

	void PlayAnimation (std::string_view animation);
	void PauseAnimation(std::string_view animation);
	void ResetAnimation(std::string_view animation);
};

