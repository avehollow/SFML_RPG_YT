#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite* sprite, float offset_x, float offset_y, float width, float height)
	: sprite(sprite)
	, offset_x(offset_x)
	, offset_y(offset_y)
{
	hitbox.setPosition(sprite->getPosition().x + offset_x, sprite->getPosition().y + offset_y);
	hitbox.setSize(sf::Vector2f(width,height));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineThickness(1.0f);
	hitbox.setOutlineColor(sf::Color::Green);
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
	hitbox.setPosition(sprite->getPosition().x + offset_x, sprite->getPosition().y + offset_y);
}

void HitboxComponent::Render(sf::RenderWindow* window)
{
	if (window)
		window->draw(hitbox);
}
