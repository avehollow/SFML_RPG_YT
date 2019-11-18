#pragma once

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

using std::make_unique;
using std::make_shared;
using std::string;
using std::to_string;

//This pointer does not manage memory; Dont try to delete ! This pointer used only for access to data
#define ACCESS_POINTER 

class HitboxComponent
{
private:
	ACCESS_POINTER  sf::Sprite*		   sprite;
					sf::RectangleShape hitbox;
					sf::FloatRect      next_position;
	
	float offset_x = 0.0f;
	float offset_y = 0.0f;

public:
	HitboxComponent(sf::Sprite* sprite, float offset_x, float offset_y, float width, float height);
	virtual ~HitboxComponent();



	bool CheckIntersect(const sf::FloatRect& rect);


	void Update();
	void Render(sf::RenderWindow* window);


	void SetPosition(const sf::Vector2f& pos);

	sf::FloatRect GetNextPosition(const sf::Vector2f& velocity);

	sf::FloatRect GetGlobalBounds()const
	{
			
		return hitbox.getGlobalBounds();

	}
	sf::Vector2f GetPosition()const
	{
		return hitbox.getPosition();
	}

	sf::FloatRect last_pos;
};

