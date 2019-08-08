#include "Player.h"



Player::Player(float posX, float posY,  sf::Sprite* sprite, sf::Texture* texture )
{
	this->sprite  = sprite;
	this->texture = texture;
	this->SetPosition(posX, posY);

	if (texture)
		this->sprite->setTexture(*texture);
	CreateMovementComponent(350.0f, 50.0f, 20.0f);



	CreateAnimationComponent(this->texture);
	animation_component->AddAnimation("IDLE",      this->texture, 0.1f, 0, 0, 13, 0, 192, 192);
	animation_component->AddAnimation("WALK_LEFT", this->texture, 0.1f, 0, 1, 11, 1, 192, 192);

	CreateHitboxComponent(0.0f, 0.0f, sprite->getGlobalBounds().width, sprite->getGlobalBounds().height);
}

Player::~Player()
{
	std::cout << "Destructor " << __func__ << "\n";
}

void Player::Update(const float& frame_time)
{
	Entity::Update(frame_time);

	if (movement_component.get())
		movement_component->Update(frame_time);

	if (animation_component.get()) {
		if (movement_component->IsIdle())
		{
			animation_component->Play("IDLE", frame_time);
		}
		else if(movement_component->GetMoveState() == MovementComponent::MOVE_LEFT)
		{
			animation_component->Play("WALK_LEFT", frame_time);
		}
		
	}

	if (hitbox_component.get())
	{
		hitbox_component->Update();
	}
}

void Player::Render(sf::RenderWindow* window)
{
	if (window)
	{
		//window->draw(*sprite);
		hitbox_component->Render(window);
	}
}
