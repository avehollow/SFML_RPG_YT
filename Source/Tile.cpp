#include "pch.h"
#include "Tile.h"


Tile::Tile(float pos_x, float pos_y, size_t size)
{
	shape.setSize(sf::Vector2f(size, size));
	shape.setPosition(pos_x, pos_y);

	texture = nullptr;

}

Tile::~Tile()
{
	static int i = 0;
	i++;
	std::cout << "\nDelete tile number: " << i;
}

void Tile::Update(const float& frame_time)
{
}

void Tile::Render(sf::RenderWindow* window) const
{
	if (texture)
	{
		window->draw(shape);
	}
}
