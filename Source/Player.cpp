#include "pch.h"
#include "Player.h"



Player::Player(float posX, float posY,  sf::Sprite* sprite, sf::Texture* texture )
{
	this->sprite  = sprite;
	this->texture = texture;
	this->SetPosition(posX, posY);

	if (texture)
		this->sprite->setTexture(*texture);

	// Set deceleration = 1000.0f to achieve slip effects 
	CreateMovementComponent(550.0f, 15000.0f, 2000.0f);

	/*
		B³¹d:
		Animation component zmienia klatke co okreslony czas wyznaczajac tym predkosc animacji. Z racj tego faktu funkcja "Play" nie odgrywa odrazu animacji co jest
		uzasadnione podczas trwania pojedynczej animacji. Niestety podczas zmiany animacji nie mo¿na czekaæ poniewa¿ powoduje to opóŸnienie. W momencie zmiany
		animacji nowa animacja powinna zostaæ odrazu odgrywana.

		Rozwi¹zanie:
		Poprawiony zosta³ animation component tak aby nowa animacja rozpoczela sie odrazu.
		Dodano animacje "BLINK" (mrugniecie) ktora wykonuje sie co 0.0f sec. Animacja jest pusta / nie zwiera zadnych tresci.

		
	*/

	CreateAnimationComponent(this->texture);
	animation_component->AddAnimation("IDLE",         this->texture, 0.11f,  0, 0, 13, 0, 192, 192);
	animation_component->AddAnimation("BLINK",        this->texture, 0.00f,  0, 0, 0,  0, 1,   1);
	animation_component->AddAnimation("WALK_LEFT",    this->texture, 0.1f,   0, 1, 11, 1, 192, 192);
	animation_component->AddAnimation("ATTACK",       this->texture, 0.05f,  4, 2, 13, 2, 384, 192);
	//animation_component->AddAnimation("ATTACK_FAST",  this->texture, 0.00f,  4, 2, 13, 2, 384, 192);

	CreateHitboxComponent(86.0f, 65.0f, 86.0f, 110.0f); //86 i 110
	movement_component->SetHitBox(hitbox_component.get());


	CreateAttributeComponent(1);
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		attribute_component->GainExp(30);
	}


	attribute_component->Update();
	system("cls");
	std::cout<<attribute_component->DebugPrint();
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
		
		if (movement_component->GetMoveState() == MovementComponent::MOVE_LEFT && !atack)
		{
			if (sprite->getScale().x < 0.0f)
			{
				sprite->setOrigin(0.0f, 0.0f);
				sprite->setScale(1.0f, 1.0f);
			}

		animation_component->Play("WALK_LEFT", frame_time, false, movement_component->GetVelocity().x, movement_component->GetMaxVelocity());
		}
		if (movement_component->GetMoveState() == MovementComponent::MOVE_RIGHT && !atack)
		{
			if (sprite->getScale().x > 0.0f)
			{
				sprite->setOrigin(258.0f, 0.0f);
				sprite->setScale(-1.0f, 1.0f);
			}
			animation_component->Play("WALK_LEFT", frame_time, false, movement_component->GetVelocity().x, movement_component->GetMaxVelocity());
		}
		if (movement_component->GetMoveState() == MovementComponent::MOVE_UP && !atack)
		{
			animation_component->Play("WALK_LEFT", frame_time);
		}
		if (movement_component->GetMoveState() == MovementComponent::MOVE_DOWN && !atack)
		{
			animation_component->Play("WALK_LEFT", frame_time);
		}
		if (movement_component->GetMoveState() == MovementComponent::ATTACK && !atack)
		{
			atack = true;
		    animation_component->Play("BLINK", frame_time);
		}
		else if (movement_component->GetMoveState() == MovementComponent::IDLE && !atack)
		{
			animation_component->Play("IDLE", frame_time);
		}

		if (atack)
		{
			if (sprite->getScale().x > 0.0f)
				sprite->setOrigin(66.0f, 0.0f); // 96.0f default
			else
				sprite->setOrigin(228.0f + 96.0f, 0.0f); //258.0f default

			if (animation_component->Play("ATTACK", frame_time))
			{
				atack = false;

				if (sprite->getScale().x > 0.0f)
					sprite->setOrigin(0.0f, 0.0f);
				else
					sprite->setOrigin(258.0f, 0.0f);
				animation_component->Play("BLINK", frame_time);
			}

		}

	}
}


