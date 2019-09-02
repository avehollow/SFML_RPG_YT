#pragma once

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

using std::make_unique;
using std::make_shared;
using std::string;
using std::vector;
using std::map;
using std::stack;
using std::pair;
using std::to_string;

//This pointer does not manage memory; Dont try to delete ! This pointer used only for access to data
#define ACCESS_POINTER 


class MovementComponent
{
public:
	enum MOVE_STATE
	{
		IDLE		= 0,
		MOVING		= 1,
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_UP,
		MOVE_DOWN,
		ATTACK
	};
private:
	ACCESS_POINTER sf::Sprite* sprite = nullptr;

	float        max_velocity	  = 250.0f;
	float		 acceleration	  = 0.0f;
	float		 deceleration	  = 0.0f; 

	sf::Vector2f velocity		  = {0.0f,0.0f};


public:
	MovementComponent(sf::Sprite* sprite, float max_velocity, float acceleration, float deceleration);
	virtual ~MovementComponent();		

	const sf::Vector2f& GetVelocity()const {
		return velocity;
	}
	const float& GetMaxVelocity()const {
		return max_velocity;
	}
	void SetMaxVelocity(const float& max_velocity) {
		this->max_velocity = max_velocity;
	}

	const bool IsIdle() const {
		return (velocity.x == 0 && velocity.y == 0) ? true : false;
	}

	MOVE_STATE GetMoveState();

	void Move(float dir_x, float dir_y);
	void Update(const float& frame_time);


};

