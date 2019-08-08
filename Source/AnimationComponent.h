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

	private:
		sf::IntRect start_pos = {};
		sf::IntRect end_pos	  = {};
		sf::IntRect curr_pos  = {};

		float time		= 0.0f;
		float speed		= 0.0f;
		int   width     = 0;
		int   height    = 0;

	public:
		Animation(sf::Sprite* sprite, sf::Texture* sheet, float speed, int start_frame_x, int start_frame_y, int end_frame_x, int end_frame_y, int width, int height)
			: sheet(sheet)
			, sprite(sprite)
			, speed(speed)
			, width(width)
			, height(height)
		{
			start_pos = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			end_pos   = sf::IntRect(end_frame_x   * width, end_frame_y   * height, width, height);
			curr_pos  = start_pos;

			this->sprite->setTexture(*sheet, true);
			this->sprite->setTextureRect(start_pos);
		}
		Animation()  = default;
		~Animation() = default;

		void Set(sf::Sprite* sprite, sf::Texture* sheet, float speed, int start_frame_x, int start_frame_y, int end_frame_x, int end_frame_y, int width, int height)
		{
			this->sheet  = sheet;
			this->sprite = sprite;
			this->speed  = speed;
			this->width  = width;
			this->height = height;

			start_pos = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			end_pos   = sf::IntRect(end_frame_x * width, end_frame_y * height, width, height);
			curr_pos  = start_pos;

			this->sprite->setTexture(*sheet, true);
			this->sprite->setTextureRect(start_pos);

			time = 0.0f;
		}


		void Play(const float& frame_time)
		{
			if (time += frame_time; time > speed)
			{
				if (curr_pos != end_pos)
				{
					curr_pos.left += width;
				}
				else
				{
					curr_pos = start_pos;
				}
				sprite->setTextureRect(curr_pos);
				time = 0.0f;
			}
		}

		// HACK Add body function
		void Reset()
		{
			curr_pos = start_pos;
			time	 = 0.0f;

			sprite->setTextureRect(curr_pos);
			
		};

	};// End class Animation

private:
	ACCESS_POINTER sf::Texture* sheet		   = nullptr;
	ACCESS_POINTER sf::Sprite*  sprite		   = nullptr;
	ACCESS_POINTER Animation*   last_animation = nullptr;
	std::map<std::string, Animation> animations;
	

public:
	AnimationComponent(sf::Sprite* sprite, sf::Texture* sheet);
	virtual ~AnimationComponent();

	void AddAnimation(std::string_view key, sf::Texture* sheet, float speed, int start_frame_x, int start_frame_y, int end_frame_x, int end_frame_y, int width, int height);
	
	void Play(std::string_view key, const float& frame_time);

};

