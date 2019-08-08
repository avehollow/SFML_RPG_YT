#pragma once

#include "Entity.h"

class Player : public Entity
{
public:

	Player(float posX, float posY, sf::Sprite* sprite, sf::Texture* texture);
	virtual ~Player();

	void Update(const float& frame_time) override;
	void Render(sf::RenderWindow* window) override;
};

