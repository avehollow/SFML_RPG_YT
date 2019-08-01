#pragma once

#include "Entity.h"

class Player : public Entity
{
public:

	Player(float posX, float posY, sf::Sprite* sprite, sf::Texture* texture = nullptr);
	virtual ~Player();
};

