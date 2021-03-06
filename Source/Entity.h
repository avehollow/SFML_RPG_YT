#pragma once

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "AttributeComponent.h"

class Entity
{
private:

protected:
	ACCESS_POINTER sf::Sprite*  sprite  = nullptr; 
	ACCESS_POINTER sf::Texture* texture = nullptr;

public:
	unique_ptr<MovementComponent>  movement_component;
	unique_ptr<AnimationComponent> animation_component;
	unique_ptr<HitboxComponent>    hitbox_component;
	unique_ptr<AttributeComponent> attribute_component;

public:
	virtual sf::Vector2f	    GetPosition();
	virtual sf::FloatRect	    GetHitboxBounds();
	virtual void				SetPosition(const float x, const float y);
	virtual	void				SetTexture(sf::Texture* texture);
	virtual void				move(const float& frame_time, float dir_x, float dir_y);
	virtual void				SetMaxVelocity(const float& max_velocity);
	virtual void				CreateMovementComponent(float max_velocity, float acceleraton, float deceleration);
	virtual void				CreateAnimationComponent(sf::Texture* sheet);
	virtual void				CreateHitboxComponent(float offset_x, float offset_y, float width, float height);
	virtual void				CreateAttributeComponent(int level);
	sf::FloatRect GetNextPostionBounds(const float& frame_time) const;
	sf::FloatRect GetSpriteGlobalBounds() const;


	virtual void StopVelocity();
	virtual void StopVelocityX();
	virtual void StopVelocityY();
	virtual const sf::Vector2i GetGridPosition(int grid_size)const;

public:
	Entity();
	virtual ~Entity();

	virtual void Update(const float& frame_time)		    ;// = 0;
	virtual void Render(sf::RenderWindow* target = nullptr) ;// = 0;

};

