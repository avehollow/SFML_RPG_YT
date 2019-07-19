#include "Entity.h"

void Entity::move(const float& frame_time, float dir_x, float dir_y)
{
	//HACK Clamp values
	dir_x = std::clamp(dir_x, -1.0f, 1.0f);
	dir_y = std::clamp(dir_y, -1.0f, 1.0f);

	shape.move(dir_x * movement_speed * frame_time, dir_y * movement_speed * frame_time);
}

Entity::Entity()
{
	shape.setSize(sf::Vector2f(50.0f, 50.0f));
}

Entity::~Entity()
{
	//HACK
	std::cout << "Destructor " << __func__ << "\n"; // State::~State()\n";
}

void Entity::Update(const float& frame_time)
{
}

void Entity::Render(sf::RenderTarget* target)
{
	if (!target) return;


		target->draw(shape);
}
