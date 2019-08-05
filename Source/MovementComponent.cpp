#include "MovementComponent.h"

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

void MovementComponent::Move(float dir_x, float dir_y)
{
	dir_x = std::clamp(dir_x, -1.0f, 1.0f);
	dir_y = std::clamp(dir_y, -1.0f, 1.0f);

	velocity.x += dir_x * acceleration;
	velocity.y += dir_y * acceleration;
	
	velocity.x = std::clamp(velocity.x, -max_velocity, max_velocity);
	velocity.y = std::clamp(velocity.y, -max_velocity, max_velocity);

}

void MovementComponent::Update(const float& frame_time)
{

	if (fabs(velocity.x) > 0 || fabs(velocity.y) > 0)
	{
		// HACK. Maybe someohter way to calculate deceleration ?
		velocity *= 1.0f - (deceleration / 100.0f);
	};
	/*if (velocity.x > 0.0f)
	{
		velocity.x -= deceleration;
		velocity.x = std::clamp(velocity.x, 0.0f, max_velocity);
	}
	if (velocity.x < 0.0f)
	{
		velocity.x += deceleration;
		velocity.x = std::clamp(velocity.x, -max_velocity, 0.0f);
	}
	if (velocity.y > 0.0f)
	{
		velocity.y -= deceleration;
		velocity.y = std::clamp(velocity.y, 0.0f, max_velocity);
	}
	if (velocity.y < 0.0f)
	{
		velocity.y += deceleration;
		velocity.y = std::clamp(velocity.y, -max_velocity, 0.0f);
	}*/

	if (sprite)
		sprite->move(this->velocity * frame_time);
}

