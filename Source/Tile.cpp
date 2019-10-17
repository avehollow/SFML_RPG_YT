#include "pch.h"
#include "Tile.h"


Tile::Tile(float pos_x, float pos_y, size_t size)
	: bCollision(false)
	, type(5)
	, texture(nullptr)
{
	shape.setSize(sf::Vector2f(size, size));
	shape.setPosition(pos_x, pos_y);

	//texture = nullptr;

}

Tile::~Tile()
{
	static int i = 0;
	i++;
	//std::cout << "\nDelete tile number: " << i;
}

void Tile::Update(const float& frame_time, bool bShowCollision)
{
	if (bShowCollision)
	{

		if (!bCollision)
		{
		    shape.setOutlineThickness(3);
			shape.setOutlineColor(sf::Color(0, 255, 0, 255));
		}
		else
		{
		    shape.setOutlineThickness(6);
	        shape.setOutlineColor(sf::Color(255, 0, 0, 255));
		}

	}
	else
	{
		 shape.setOutlineThickness(0);
	}
}

void Tile::Render(sf::RenderWindow* window) const
{

	if (texture)
	{
		window->draw(shape);
	}

}

bool Tile::intersects(const sf::FloatRect bounds) const
{
	return shape.getGlobalBounds().intersects(bounds) && bCollision;
}

const std::string Tile::PlaceTileInfoToString()
{
	int t = (texture == nullptr ? 0 : 1);
	std::stringstream ss;
	ss  << t
		<< " "
		<< bCollision
		<< " "
		<< type
		<< " "
		<< shape.getTextureRect().left
		<< " "
		<< shape.getTextureRect().top
		<< " ";
		
	return ss.str();
}
