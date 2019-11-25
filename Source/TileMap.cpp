#include "pch.h"
#include "TileMap.h"
#include "State.h" //include Entity.h




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
		 map[pos_x][pos_y][pos_z]->texture    = nullptr;
		 map[pos_x][pos_y][pos_z]->bCollision = false;
		 map[pos_x][pos_y][pos_z]->type       = 0;
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

void TileMap::Render(sf::RenderWindow* window, Entity* entity)
{
	////
	// Tiles
	////
	if (entity)
	{


		fromX = entity->GetPosition().x / size_grid - 10;
		fromY = entity->GetPosition().y / size_grid - 10;

		toX = entity->GetPosition().x / size_grid + 15;
		toY = entity->GetPosition().y / size_grid + 10;


		if (fromX < 0)
			fromX = 0;

		if (toX > map.size())
			toX = map.size();

		if (fromY < 0)
			fromY = 0;

		if (toY > map[0].size())
			toY = map[0].size();

		//std::cout << "\n " << fromX << " " << toX;
		//std::cout << "\n " << fromY << " " << toY;
		//system("cls");

		for (size_t x = fromX; x < toX; x++)
		{
			for (size_t y = fromY; y < toY; y++)
			{
				for (size_t i = 0; i < 3; i++)
				{
					map[x][y][i]->Render(window);
				}
			}
		}
	}
	else
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



}

void TileMap::UpdateCollision(Entity* entity,const float& frame_time)
{

		// IMPORTANT!
		// enitity->GetPosition() return hitbox_component position because all stuff (like sprite) are pinned to hitbox

		// IMPORTANT!
	    // entity->SetPosition() set hitbox_component position! because all stuff (like sprite) are pinned to hitbox
	
    // Left-Top Corner map
	if (entity->GetNextPostionBounds(frame_time).left < 0.0f)
	{
		entity->movement_component->StopVelocityX();
		entity->SetPosition(0, entity->GetPosition().y);
	}

	if (entity->GetNextPostionBounds(frame_time).top < 0.0f)
	{
		entity->movement_component->StopVelocityY();
		entity->SetPosition(entity->GetPosition().x, 0);
	}

	// Right-Bottom Corner map
	if (entity->GetNextPostionBounds(frame_time).left+ 
		entity->hitbox_component->GetGlobalBounds().width > size_grid * map.size())
	{
		entity->movement_component->StopVelocityX();
		entity->SetPosition(size_grid * map.size() - entity->hitbox_component->GetGlobalBounds().width, entity->GetPosition().y);
	}

	if (entity->GetNextPostionBounds(frame_time).top +
		entity->hitbox_component->GetGlobalBounds().height > size_grid * map[0].size())
	{
		entity->movement_component->StopVelocityY();
		entity->SetPosition(entity->GetPosition().x, size_grid * map[0].size() - entity->hitbox_component->GetGlobalBounds().height);
	}

	////
	// Tiles
	////


	fromX = entity->GetPosition().x / size_grid - 2;
	fromY = entity->GetPosition().y / size_grid - 2;

	// AVE Sometimes issue with wrong calculate collision are made by wrong values HERE 
	// If someone object has very large collision component them we need increase these values below
	toX = entity->GetPosition().x / size_grid + (1 + (entity->hitbox_component->GetGlobalBounds().width) / 70);
	toY = entity->GetPosition().y / size_grid + (2 + (entity->hitbox_component->GetGlobalBounds().height) / 70);
	std::cout << "\n X:" << toX;
	std::cout << "\n Y:" << toY;

	if (fromX < 0)
		fromX = 0;

	if (toX > map.size())
		toX = map.size() - 2;

	if (fromY < 0)
		fromY = 0;

	if (toY > map[0].size())
		toY = map[0].size() - 2;
	
	 
	for (size_t x = fromX; x < toX; x++)
	{
		for (size_t y = fromY; y < toY; y++)
		{
			for (size_t i = 0; i < 3; i++)
			{
				sf::FloatRect player_bounds = entity->GetHitboxBounds();
				sf::FloatRect wall_bounds   = map[x][y][i]->shape.getGlobalBounds();
				sf::FloatRect next_position = entity->GetNextPostionBounds(frame_time);
				
				if (map[x][y][i]->intersects(next_position))
				{
					map[x][y][i]->shape.setFillColor(sf::Color::Red);



					// bottom collision (ENTITY BOTTOM !!)
					if (player_bounds.top < wall_bounds.top
						&& player_bounds.top + player_bounds.height < wall_bounds.top +wall_bounds.height
						&& player_bounds.left < wall_bounds.left + wall_bounds.width
						&& player_bounds.left + player_bounds.width > wall_bounds.left)
					{
						entity->movement_component->StopVelocityY();
						entity->SetPosition(player_bounds.left, wall_bounds.top - player_bounds.height);
					}	

					// top (ENTITY TOP !!)
					 else if (player_bounds.top > wall_bounds.top
						&& player_bounds.top + player_bounds.height > wall_bounds.top + wall_bounds.height
						&& player_bounds.left < wall_bounds.left + wall_bounds.width
						&& player_bounds.left + player_bounds.width > wall_bounds.left)
					{
						entity->movement_component->StopVelocityY();
						entity->SetPosition(player_bounds.left, wall_bounds.top + wall_bounds.height);
					}


					// right (ENTITY RIGHT !!)
					if (player_bounds.left < wall_bounds.left
						&& player_bounds.left + player_bounds.width < wall_bounds.left + wall_bounds.width
						&& player_bounds.top < wall_bounds.top + wall_bounds.height
						&& player_bounds.top + player_bounds.height > wall_bounds.top)
					{
						entity->movement_component->StopVelocityX();
						entity->SetPosition(wall_bounds.left - player_bounds.width, player_bounds.top);
					}

					// left (ENTITY LEFT !!)
					 else if (player_bounds.left > wall_bounds.left
						&& player_bounds.left + player_bounds.width > wall_bounds.left + wall_bounds.width
						&& player_bounds.top < wall_bounds.top + wall_bounds.height
						&& player_bounds.top + player_bounds.height > wall_bounds.top)
					{
						entity->movement_component->StopVelocityX();
						entity->SetPosition(wall_bounds.left + wall_bounds.width, player_bounds.top);
					}

					


				


				}
			}
		}
	}
}
