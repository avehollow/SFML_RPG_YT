#pragma once

#include "MovementComponent.h"


class Entity
{
private:

protected:
	ACCESS_POINTER sf::Sprite*  sprite  = nullptr; 
	ACCESS_POINTER sf::Texture* texture = nullptr;
	
	unique_ptr<MovementComponent> movement_component;

public:
	virtual const sf::Vector2f& GetPosition();
	virtual void				SetPosition(const float x, const float y);
	virtual	void				SetTexture(sf::Texture* texture);
	virtual void				move(const float& frame_time, float dir_x, float dir_y);
	virtual void				SetMaxVelocity(const float& max_velocity);
	virtual void				CreateMovementComponent(sf::Sprite* sprite, float max_velocity, float acceleraton, float deceleration);

public:
	Entity();
	virtual ~Entity();

	virtual void Update(const float& frame_time)		    ;// = 0;
	virtual void Render(sf::RenderTarget* target = nullptr) ;// = 0;

};

