#pragma once
#include "Tile.h"


class TileMap
{
private:
	// The first two vectors represent the 2D map [X,Y]
	// Third vectors are the layers on which the textures will be placed [Z]
	// for example. 1layers-->grass   2layers-->road   3layers--->tree

	std::vector<
		std::vector<
			std::vector<std::unique_ptr<Tile>> >> map;

	size_t size_grid = 100;
	size_t size_x    = 10;
	size_t size_y    = 10;
	size_t layers	 = 3;

	sf::Texture* texture_sheet;
public:
	TileMap(sf::Texture* texture_sheet);
	~TileMap();

	void AddTile(int pos_x, int pos_y, int pos_z, sf::IntRect rect);
	void RemoveTile(int pos_x, int pos_y, int pos_z);
	void Update(const float& frame_time);
	void Render(sf::RenderWindow* window);
};

