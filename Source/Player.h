#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
	bool atack = false;
public:

	Player(float posX, float posY, sf::Sprite* sprite, sf::Texture* texture);
	virtual ~Player();


	void UpdateAnimation(const float& frame_time);
	void Update(const float& frame_time) override;
	void Render(sf::RenderWindow* window) override;
};

