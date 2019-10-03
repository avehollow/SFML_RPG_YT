#include "pch.h"
#include "TileMap.h"
#include "State.h"


using std::vector;

TileMap::TileMap(sf::Texture* texture_sheet, StateData* sd)
	: texture_sheet(texture_sheet)
{
	if (sd)
	{
		size_grid = sd->tile_size;
		size_x    = sd->grid_size_x;
		size_y    = sd->grid_size_y;
	}
}

void TileMap::CreateMap()
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

void TileMap::AddTile(int pos_x, int pos_y, int pos_z, sf::IntRect rect, bool collision)
{
	if (pos_x >= 0 && pos_x < size_x &&
		pos_y >= 0 && pos_y < size_y &&
		pos_z >= 0 && pos_z < layers)
	{
		map[pos_x][pos_y][pos_z]->texture = texture_sheet;
		map[pos_x][pos_y][pos_z]->shape.setTexture(texture_sheet);
		map[pos_x][pos_y][pos_z]->shape.setTextureRect(rect);
		map[pos_x][pos_y][pos_z]->bCollision = !collision;
	}
}
void TileMap::RemoveTile(int pos_x, int pos_y, int pos_z)
{
	if (pos_x >= 0 && pos_x < size_x &&
		pos_y >= 0 && pos_y < size_y &&
		pos_z >= 0 && pos_z < layers)
	{
		 map[pos_x][pos_y][pos_z]->texture = nullptr;
	}
}
void TileMap::SaveToFile() 
{
	// size_grid
	// size_x
	// size_y
	// layers

	std::ofstream output("Data/Maps/map0.txt");
	if (output.is_open())
	{
		output << size_grid
			   << " "
			   << size_x
			   << " "
			   << size_y
			   << " "
			   << layers
			   << " ";
		

		for (size_t x = 0; x < size_x; x++)
		{
			for (size_t y = 0; y < size_y; y++)
			{
				for (size_t z = 0; z < layers; z++)
				{

					output << map[x][y][z]->PlaceTileInfoToString();
					/*int texture = map[x][y][z]->texture == nullptr ? 0 : 1;
					output << texture 
						   << " "
						   << map[x][y][z]->shape.getTextureRect().left
						   << " "
						   << map[x][y][z]->shape.getTextureRect().top
						   << " ";*/
				}
			}
		}
	}
	output.close();
}
void TileMap::LoadFromFile()
{
	std::ifstream input("Data/Maps/map0.txt");

	int tex  = 0;
	int l    = 0;
	int t    = 0;
	int b    = 0;
	int type = 0;

	if (input.is_open())
	{


		input >> size_grid
			  >> size_x
			  >> size_y
			  >> layers;

		// textura
		// kolizja
		// typ
		// left
		// top

		CreateMap();

		for (size_t x = 0; x < size_x; x++)
		{
			for (size_t y = 0; y < size_y; y++)
			{
				for (size_t z = 0; z < layers; z++)
				{
					input >> tex >> b >> type >> l >> t;
					if (tex == 1)
					{
						map[x][y][z]->texture = texture_sheet;
					}
					map[x][y][z]->type = t;
					map[x][y][z]->bCollision = b;
					map[x][y][z]->shape.setTexture(texture_sheet);
					map[x][y][z]->shape.setTextureRect(sf::IntRect(l, t, 100, 100));
				}
			}
		}
	}
	else
	{
		CreateMap();
	}

	input.close();
}
void TileMap::Update(const float& frame_time, bool bShowCollision)
{
	for (const auto& column : map)
	{
		for (const auto& row : column)
		{
			for (const auto& tile : row)
			{
				if (tile.get())
				{
					tile->Update(frame_time, bShowCollision);
				}
			}
		}
	}
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
