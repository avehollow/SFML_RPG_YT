#include "pch.h"
#include "MovementComponent.h"
#include "HitboxComponent.h"

MovementComponent::MovementComponent(sf::Sprite* sprite, float max_velocity, float acceleration, float deceleration)
	: sprite(sprite)
	, max_velocity(max_velocity)
	, acceleration(acceleration)
	, deceleration(deceleration)
{
	this->max_velocity = fabs(max_velocity);
	this->acceleration = fabs(acceleration);
	this->deceleration = fabs(deceleration);
}

MovementComponent::~MovementComponent()
{
	std::cout << "Destructor " << __func__ << "\n";
}

MovementComponent::MOVE_STATE MovementComponent::GetMoveState()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		return ATTACK;

	if (velocity.x > 0)
		return MOVE_RIGHT;

	if (velocity.x < 0)
		return MOVE_LEFT;

	if (velocity.y > 0)
		return MOVE_DOWN;

	if (velocity.y < 0)
		return MOVE_UP;

	if (velocity.x == 0 && velocity.y == 0)
		return IDLE;
	

}

void MovementComponent::Move(const float& frame_time,float dir_x, float dir_y)
{
	dir_x = std::clamp(dir_x, -1.0f, 1.0f);
	dir_y = std::clamp(dir_y, -1.0f, 1.0f);

	velocity.y += dir_y * acceleration* frame_time;
	velocity.x += dir_x * acceleration* frame_time;
	
	velocity.x = std::clamp(velocity.x, -max_velocity, max_velocity);
	velocity.y = std::clamp(velocity.y, -max_velocity, max_velocity);

}

void MovementComponent::Update(const float& frame_time)
{

	//if (fabs(velocity.x) > 0 || fabs(velocity.y) > 0)
	//{
	//	// HACK. Maybe someohter way to calculate deceleration ?
	//	velocity *= 1.0f - (deceleration / 100.0f);

	//	fabs(velocity.x) < 9 ? velocity.x = 0 : velocity.x;
	//	fabs(velocity.y) < 9 ? velocity.y = 0 : velocity.y;
	//};

	
	if (velocity.x > 0.0f)
	{
		velocity.x -= deceleration * frame_time;
		velocity.x = std::clamp(velocity.x, 0.0f, max_velocity);
	}
	if (velocity.x < 0.0f)
	{
		velocity.x += deceleration * frame_time;
		velocity.x = std::clamp(velocity.x, -max_velocity, 0.0f);
	}
	if (velocity.y > 0.0f)
	{
		velocity.y -= deceleration * frame_time;
		velocity.y = std::clamp(velocity.y, 0.0f, max_velocity);
	}
	if (velocity.y < 0.0f)
	{
		velocity.y += deceleration * frame_time;
		velocity.y = std::clamp(velocity.y, -max_velocity, 0.0f);
	}

	if (sprite)
	{
		sprite->move(this->velocity * frame_time);
	}
}

