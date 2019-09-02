#pragma once

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
		sf::IntRect last_pos  = {};

		float time		= 99.0f; 
		float speed		= 0.0f;
		int   width     = 0;
		int   height    = 0;
		bool  completed = false;

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
			last_pos = sf::IntRect((end_frame_x - 1) * width, (end_frame_y - 1) * height, width, height);
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
			last_pos  = sf::IntRect((end_frame_x-1) * width, (end_frame_y) * height, width, height);
			curr_pos  = start_pos;

			this->sprite->setTexture(*sheet, true);
			this->sprite->setTextureRect(start_pos);

			time = 99.0f;
		}


		void Play(const float& frame_time, float modifier_percent)
		{
			float mod = fabs(modifier_percent);
			if (mod < 0.5f){
				mod = 0.5f;
			}
		
			completed = false;

			if (time += mod * frame_time; time > speed)
			{
				if (curr_pos != end_pos)
				{
					curr_pos.left += width;
				}
				else
				{
					curr_pos = start_pos;
					completed = true;
				}
				time = 0.0f;
			}
			sprite->setTextureRect(curr_pos);
		}

	
		void Reset()
		{
			curr_pos  = start_pos;
			time	  = 99.0f;
			completed = false;
		};

		bool IsCompleted() const {
			return completed;
		}

	};// End class Animation

private:
	ACCESS_POINTER sf::Texture* sheet			   = nullptr;
	ACCESS_POINTER sf::Sprite*  sprite			   = nullptr;
	ACCESS_POINTER Animation*   last_animation	   = nullptr;
	ACCESS_POINTER Animation*   priority_animation = nullptr;
	std::map<std::string, Animation> animations;
	

public:
	AnimationComponent(sf::Sprite* sprite, sf::Texture* sheet);
	virtual ~AnimationComponent();

	void AddAnimation(std::string_view key, sf::Texture* sheet, float speed, int start_frame_x, int start_frame_y, int end_frame_x, int end_frame_y, int width, int height);
	
	bool Play(std::string_view key, const float& frame_time, bool priority = false, float modifier = 1.0f, float modifier_max = 1.0f);

};

