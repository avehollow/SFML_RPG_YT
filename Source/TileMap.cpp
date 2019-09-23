#include "pch.h"
#include "TileMap.h"

using std::vector;
TileMap::TileMap(sf::Texture* texture_sheet)
	: texture_sheet(texture_sheet)
{
	map.reserve(size_x);
	for (size_t x = 0; x < size_x; x++)
	{
		map.emplace_back(vector<vector<std::unique_ptr<Tile>>>{});;
		map[x].reserve(size_y);
		for (size_t y = 0; y < size_y; y++)
		{
			map[x].emplace_back(vector<std::unique_ptr<Tile>>{});
			map[x][y].reserve(layers);
			for (size_t z = 0; z < layers; z++)
			{
				map[x][y].emplace_back(std::unique_ptr<Tile>(std::make_unique<Tile>(x * size_grid, y * size_grid, size_grid)));
			}
		}
	}
}

TileMap::~TileMap()
{
}

void TileMap::AddTile(int pos_x, int pos_y, int pos_z, sf::IntRect rect)
{
	if (pos_x >= 0 && pos_x < size_x &&
		pos_y >= 0 && pos_y < size_y &&
		pos_z >= 0 && pos_z < layers)
	{
		if (pos_z == 0)
		{
			map[pos_x][pos_y][pos_z]->shape.setTexture(texture_sheet);
			map[pos_x][pos_y][pos_z]->texture = texture_sheet;
			map[pos_x][pos_y][pos_z]->shape.setTextureRect(rect);
		}
		
		if (pos_z == 1)
		{
			map[pos_x][pos_y][pos_z]->shape.setTexture(texture_sheet);
			map[pos_x][pos_y][pos_z]->texture = texture_sheet;
			map[pos_x][pos_y][pos_z]->shape.setTextureRect(rect);
		}
		
		if (pos_z == 2)
		{
			map[pos_x][pos_y][pos_z]->shape.setTexture(texture_sheet);
			map[pos_x][pos_y][pos_z]->texture = texture_sheet;
			map[pos_x][pos_y][pos_z]->shape.setTextureRect(rect);
		}
			
	}
}
void TileMap::RemoveTile(int pos_x, int pos_y, int pos_z)
{
	sf::Sprite a;
	
	if (pos_x >= 0 && pos_x < size_x &&
		pos_y >= 0 && pos_y < size_y &&
		pos_z >= 0 && pos_z < layers)
	{
		if (pos_z == 0) map[pos_x][pos_y][pos_z]->texture = nullptr;

		if (pos_z == 1) map[pos_x][pos_y][pos_z]->texture = nullptr;

		if (pos_z == 2) map[pos_x][pos_y][pos_z]->texture = nullptr;
	
	}
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
				if (tile.get())
				{
					tile->Render(window);
				}
			}
		}
	}
}
