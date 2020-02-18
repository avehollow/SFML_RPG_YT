#include "pch.h"
#include "Entity.h"

void Entity::SetPosition(const float x, const float y)
{
	if (hitbox_component)
		hitbox_component->SetPosition(sf::Vector2f(x, y));
	else if (sprite)
		sprite->setPosition(x, y);
}

void Entity::SetTexture(sf::Texture* texture)
{
	if(texture)
		this->texture = texture;
}

sf::Vector2f Entity::GetPosition()
{
	if (hitbox_component)
		return hitbox_component->GetPosition();

	if (sprite)
		return sprite->getPosition();
	else
		return sf::Vector2f(0.0f, 0.0f);
	
}

sf::FloatRect Entity::GetHitboxBounds()
{
	if (hitbox_component)
	{
		return hitbox_component->GetGlobalBounds();
	}
	else
		return sf::FloatRect{};
}

void Entity::move(const float& frame_time, float dir_x, float dir_y)
{
	//HACK Clamp values
	dir_x = std::clamp(dir_x, -1.0f, 1.0f);
	dir_y = std::clamp(dir_y, -1.0f, 1.0f);

	if (movement_component.get())
	{
		movement_component->Move(frame_time,dir_x, dir_y);
	}

}

void Entity::SetMaxVelocity(const float& max_velocity)
{
	if(movement_component.get())
		movement_component->SetMaxVelocity(max_velocity);
}

void Entity::CreateMovementComponent(float max_velocity, float acceleraton, float deceleration)
{
	movement_component = make_unique<MovementComponent>(sprite, max_velocity, acceleraton, deceleration);
}

void Entity::CreateAnimationComponent(sf::Texture* sheet)
{
	animation_component = make_unique<AnimationComponent>(sprite, sheet);
}

void Entity::CreateHitboxComponent(float offset_x, float offset_y, float width, float height)
{
	hitbox_component = make_unique<HitboxComponent>(sprite, offset_x, offset_y, width, height);
}

void Entity::CreateAttributeComponent(int level)
{
	attribute_component = make_unique<AttributeComponent>(level) ;
}

sf::FloatRect Entity::GetNextPostionBounds(const float &frame_time) const
{

	return hitbox_component->GetNextPosition(movement_component->GetVelocity() * frame_time);
}

sf::FloatRect Entity::GetSpriteGlobalBounds() const
{
	return sprite->getGlobalBounds();
}

void Entity::StopVelocity()
{	
	if(movement_component)	
		movement_component->StopVelocity();
}

void Entity::StopVelocityX()
{	
	if(movement_component)
		movement_component->StopVelocityX();
}

void Entity::StopVelocityY()
{	
	if(movement_component)
		movement_component->StopVelocityY();
}

const sf::Vector2i Entity::GetGridPosition(int grid_size) const
{
	if (hitbox_component)
	{
		return sf::Vector2i(
			(int)hitbox_component->GetPosition().x / grid_size,
			(int)hitbox_component->GetPosition().y / grid_size
		);
	}

	if (sprite)
	{
		return sf::Vector2i(
			(int)sprite->getPosition().x / grid_size,
			(int)sprite->getPosition().y / grid_size
			);
	}
	return sf::Vector2i();
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
	
}

void Entity::Render(sf::RenderWindow* target)
{
	if (!target) return;

	if(sprite)
		target->draw(*sprite);
}
