#include "Player.h"



Player::Player(float posX, float posY,  sf::Sprite* sprite, sf::Texture* texture )
{
	this->sprite  = sprite;
	this->texture = texture;
	this->SetPosition(posX, posY);

	if (texture)
		this->sprite->setTexture(*texture);

	
	CreateMovementComponent(sprite, 350.0f, 10.0f, 1.0f);
	SetMaxVelocity(350.0f);
}

Player::~Player()
{
	std::cout << "Destructor " << __func__ << "\n";
}
