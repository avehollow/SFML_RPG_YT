#include "pch.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite* sprite, float offset_x, float offset_y, float width, float height)
	: sprite(sprite)
	, offset_x(offset_x)
	, offset_y(offset_y)
	, next_position{0,0, width, height}
{
	hitbox.setSize(sf::Vector2f(width,height));
	hitbox.setPosition(sprite->getPosition().x + offset_x, sprite->getPosition().y + offset_y);
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineThickness(-1.0f);
	hitbox.setOutlineColor(sf::Color::Green);

	next_position.left   = 0.0f;
	next_position.top    = 0.0f;
	next_position.width  = width;
	next_position.height = height;
}

HitboxComponent::~HitboxComponent()
{
	std::cout << "Destructor " << __func__ << "\n";
}

bool HitboxComponent::CheckIntersect(const sf::FloatRect& rect)
{
	return hitbox.getGlobalBounds().intersects(rect);
}

void HitboxComponent::Update()
{
	last_pos = hitbox.getGlobalBounds();

	last_pos.left =  hitbox.getPosition().x;
	last_pos.top  =  hitbox.getPosition().y;

	hitbox.setPosition(sprite->getPosition().x + offset_x, sprite->getPosition().y + offset_y);
}

void HitboxComponent::Render(sf::RenderWindow* window)
{
	if (window)
		window->draw(hitbox);
}

void HitboxComponent::SetPosition(const sf::Vector2f& pos)
{
	//HLOG Some change
	hitbox.setPosition(pos);
	sprite->setPosition(hitbox.getPosition().x - offset_x, hitbox.getPosition().y - offset_y);
}

sf::FloatRect HitboxComponent::GetNextPosition(const sf::Vector2f& velocity)
{
	//AVE  NEED multiply by frame_time
	// Solved
	next_position.left = hitbox.getPosition().x + velocity.x ;
	next_position.top  = hitbox.getPosition().y + velocity.y ;


	return next_position;
}
