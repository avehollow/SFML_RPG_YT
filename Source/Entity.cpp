#include "Entity.h"

void Entity::SetPosition(const float x, const float y)
{
	if (sprite)
		sprite->setPosition(x, y);
}

void Entity::SetTexture(sf::Texture* texture)
{
	if(texture)
		this->texture = texture;
}

const sf::Vector2f& Entity::GetPosition()
{
	if (sprite)
		return sprite->getPosition();
	else
		return sf::Vector2f(0.0f, 0.0f);
	
}

void Entity::move(const float& frame_time, float dir_x, float dir_y)
{
	//HACK Clamp values
	dir_x = std::clamp(dir_x, -1.0f, 1.0f);
	dir_y = std::clamp(dir_y, -1.0f, 1.0f);

	if (movement_component)
	{
		movement_component->Move(dir_x, dir_y);
	}

}

void Entity::SetMaxVelocity(const float& max_velocity)
{
	if(movement_component)
		movement_component->SetMaxVelocity(max_velocity);
}

void Entity::CreateMovementComponent(sf::Sprite* sprite, float max_velocity, float acceleraton, float deceleration)
{
	movement_component = make_unique<MovementComponent>(sprite, max_velocity, acceleraton, deceleration);
}

Entity::Entity()
{
	
}

Entity::~Entity()
{
	std::cout << "Destructor " << __func__ << "\n"; 
}

void Entity::Update(const float& frame_time)
{
	movement_component->Update(frame_time);
}

void Entity::Render(sf::RenderTarget* target)
{
	if (!target) return;

	if(sprite)
		target->draw(*sprite);
}
