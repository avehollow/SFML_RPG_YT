#include "Player.h"



Player::Player(float posX, float posY,  sf::Sprite* sprite, sf::Texture* texture )
{
	this->sprite  = sprite;
	this->texture = texture;
	this->SetPosition(posX, posY);

	if (texture)
		this->sprite->setTexture(*texture);
	CreateMovementComponent(550.0f, 30.0f, 4.0f);



	CreateAnimationComponent(this->texture);
	animation_component->AddAnimation("IDLE",      this->texture, 0.12f, 0, 0, 13, 0, 192, 192);
	animation_component->AddAnimation("WALK_LEFT", this->texture, 0.1f,  0, 1, 11, 1, 192, 192);
	animation_component->AddAnimation("ATTACK",    this->texture, 0.09f, 4, 2, 13, 2, 384, 192);

	CreateHitboxComponent(86.0f, 65.0f, 86.0f, 110.0f);
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

	if (hitbox_component.get())
		hitbox_component->Update();

	UpdateAnimation(frame_time);
}

void Player::Render(sf::RenderWindow* window)
{
	if (window)
	{
		// Draw sprite
		Entity::Render(window);
		hitbox_component->Render(window);
	}
}



void Player::UpdateAnimation(const float& frame_time)
{
	if (animation_component.get()) 
	{
		
		if (movement_component->IsIdle() && !atack)
		{
			animation_component->Play("IDLE", frame_time);
		}
		else if (movement_component->GetMoveState() == MovementComponent::MOVE_LEFT && !atack)
		{
				sprite->setOrigin(0.0f, 0.0f);
				sprite->setScale(1.0f, 1.0f);

			animation_component->Play("WALK_LEFT", frame_time, false, movement_component->GetVelocity().x, movement_component->GetMaxVelocity());
		}
		else if (movement_component->GetMoveState() == MovementComponent::MOVE_RIGHT && !atack)
		{
				sprite->setOrigin(258.0f, 0.0f);
				sprite->setScale(-1.0f, 1.0f);
			
			animation_component->Play("WALK_LEFT", frame_time, false, movement_component->GetVelocity().x, movement_component->GetMaxVelocity());
		}
		else if (movement_component->GetMoveState() == MovementComponent::MOVE_UP && !atack)
		{
			animation_component->Play("WALK_LEFT", frame_time);
		}
		else if (movement_component->GetMoveState() == MovementComponent::MOVE_DOWN && !atack)
		{
			animation_component->Play("WALK_LEFT", frame_time);
		}
		if (movement_component->GetMoveState() == MovementComponent::ATTACK && !atack)
		{
			atack = true;

			if (sprite->getScale().x > 0.0f)
				sprite->setOrigin(96.0f, 0.0f);
			else
				sprite->setOrigin(258.0f + 96.0f, 0.0f);
		}

		if (atack)
		{
			if (animation_component->Play("ATTACK", frame_time))
			{
				if (sprite->getScale().x > 0.0f)
					sprite->setOrigin(0.0f, 0.0f);
				else
					sprite->setOrigin(258.0f, 0.0f);

				atack = false;
			}

		}

	}

}
