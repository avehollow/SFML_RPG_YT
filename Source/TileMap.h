#pragma once
#include "Tile.h"


class TileMap
{
private:
	std::vector<
		std::vector<
			std::vector<Tile> >> map;

	unsigned size_grid = 50;
	unsigned size_x    = 10;
	unsigned size_y    = 10;
	unsigned layers	   = 1;

public:
	TileMap();
	~TileMap();

	void Update(const float& frame_time);
	void Render(sf::RenderWindow* window);
};

