#include "pch.h"
#include "TileMap.h"

using std::vector;
TileMap::TileMap()
{
	map.reserve(size_x * size_y);
	for (size_t x = 0; x < size_x; x++)
	{
		map.emplace_back(vector<vector<Tile>>{});
		for (size_t y = 0; y < size_y; y++)
		{
			map[x].emplace_back(vector<Tile>{});
			for (size_t z = 0; z < layers; z++)
			{
				map[x][y].emplace_back(Tile(x * size_grid, y * size_grid, size_grid));
			}
		}
	}

}

TileMap::~TileMap()
{
}

void TileMap::Update(const float& frame_time)
{

}

void TileMap::Render(sf::RenderWindow* window)
{
	for (const auto& column:map)
	{
		for (const auto& row : column)
		{
			for (const auto& tile : row)
			{
				tile.Render(window);
			}
		}
	}
}
