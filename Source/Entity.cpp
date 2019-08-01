#include "Entity.h"

void Entity::SetPosition(const float x, const float y)
{
	if (sprite)
		sprite->setPosition(x, y);
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

	if (sprite)
		sprite->move(dir_x * movement_speed * frame_time, dir_y * movement_speed * frame_time);

}

Entity::Entity()
{

}

Entity::~Entity()
{
	//HACK
	std::cout << "Destructor " << __func__ << "\n"; 
}

void Entity::Update(const float& frame_time)
{
}

void Entity::Render(sf::RenderTarget* target)
{
	if (!target) return;

	if(sprite)
		target->draw(*sprite);
}
