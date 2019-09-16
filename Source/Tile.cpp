#include "pch.h"
#include "Tile.h"


Tile::Tile(float pos_x, float pos_y, size_t size)
{
	shape.setSize(sf::Vector2f(size, size));
	shape.setPosition(pos_x, pos_y);
	
	static int i = 0;
	i++;
	if (i % 2 == 0)
	{
		shape.setFillColor(sf::Color::White);
	}
	else
		shape.setFillColor(sf::Color::Black);
}

Tile::~Tile()
{
}

void Tile::Update(const float& frame_time)
{
}

void Tile::Render(sf::RenderWindow* window) const
{
	window->draw(shape);
}
