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

void TileMap::Render(sf::RenderWindow* window, Entity* entity)
{
	////
	// Tiles
	////
	if (entity)
	{


		fromX = entity->GetPosition().x / size_grid - 3;
		fromY = entity->GetPosition().y / size_grid - 3;

		toX = entity->GetPosition().x / size_grid + 4;
		toY = entity->GetPosition().y / size_grid + 4;


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

void TileMap::UpdateCollision(Entity* entity)
{

		// IMPORTANT!
		// enitity->GetPosition() return hitbox_component position because all stuff (like sprite) are pinned to hitbox

		// IMPORTANT!
	    // entity->SetPosition() set hitbox_component position! because all stuff (like sprite) are pinned to hitbox

    // Left-Top Corner map
	if (entity->GetPosition().x < 0.0f)
	{
		entity->SetPosition(entity->hitbox_component->last_pos.left, entity->GetPosition().y);
		entity->movement_component->StopVelocityX();
	}

	if (entity->GetPosition().y < 0.0f)
	{
		entity->SetPosition(entity->GetPosition().x, entity->hitbox_component->last_pos.top);
		entity->movement_component->StopVelocityY();
	}

	// Right-Bottom Corner map
	if (entity->GetPosition().x + 
		entity->hitbox_component->GetGlobalBounds().width > size_grid * map.size())
	{
		entity->SetPosition(size_grid * map.size() - entity->hitbox_component->GetGlobalBounds().width, entity->hitbox_component->last_pos.top);
		entity->movement_component->StopVelocityX();
	}

	if (entity->GetPosition().y + 
		entity->hitbox_component->GetGlobalBounds().height > size_grid * map[0].size())
	{
		entity->SetPosition(entity->hitbox_component->last_pos.left, size_grid * map[0].size() - entity->hitbox_component->GetGlobalBounds().height);
		entity->movement_component->StopVelocityY();
	}

	////
	// Tiles
	////

	fromX = entity->GetPosition().x / size_grid - 3;
	fromY = entity->GetPosition().y / size_grid - 3;

	toX   = entity->GetPosition().x / size_grid + 4;
	toY   = entity->GetPosition().y / size_grid + 4;


	if (fromX < 0)
		fromX = 0;

	if (toX > map.size())
		toX = map.size() - 2;

	if (fromY < 0)
		fromY = 0;

	if (toY > map[0].size())
		toY = map[0].size() - 2;
	
	//std::cout << "\n " << fromX << " " << toX;
	//std::cout << "\n " << fromY << " " << toY;
	//system("cls");
	 
	for (size_t x = fromX; x < toX; x++)
	{
		for (size_t y = fromY; y < toY; y++)
		{
			for (size_t i = 0; i < 3; i++)
			{
				if (map[x][y][0]->intersects(entity->GetHitboxBounds()))
				{
					map[x][y][0]->shape.setFillColor(sf::Color::Red);

					sf::FloatRect wall_bounds   = map[x][y][0]->shape.getGlobalBounds();
					sf::FloatRect player_bounds = entity->GetHitboxBounds();


						//// Works fine
						//if (entity->movement_component->GetVelocity().x != 0.0f) // Left
						//{
						//	entity->movement_component->StopVelocityX();
						//	entity->SetPosition(entity->hitbox_component->last_pos.left, entity->GetPosition().y);

						//	if (entity->movement_component->GetVelocity().y < 0)
						//	{
						//		sf::FloatRect b = entity->GetHitboxBounds();
						//		sf::FloatRect a(b.left, b.top - 1, b.width, b.height);

						//		if (!map[x][y][0]->intersects(a))
						//		{
						//			return;
						//		}
						//	}

						//	if (entity->movement_component->GetVelocity().y > 0)
						//	{
						//		sf::FloatRect b = entity->GetHitboxBounds();
						//		sf::FloatRect a(b.left, b.top + 1, b.width, b.height);

						//		if (!map[x][y][0]->intersects(a))
						//		{
						//			return;
						//		}
						//	}
						//}
					
						//if (entity->movement_component->GetVelocity().y != 0.0f) // Top
						//{
						//	entity->movement_component->StopVelocityY();
						//	entity->SetPosition(entity->GetPosition().x, entity->hitbox_component->last_pos.top);

						//	if (entity->movement_component->GetVelocity().x < 0)
						//	{
						//		sf::FloatRect b = entity->GetHitboxBounds();
						//		sf::FloatRect a(b.left - 1, b.top, b.width, b.height);

						//		if (!map[x][y][0]->intersects(a))
						//		{
						//			return;
						//		}
						//	}

						//	if (entity->movement_component->GetVelocity().x > 0)
						//	{
						//		sf::FloatRect b = entity->GetHitboxBounds();
						//		sf::FloatRect a(b.left + 1, b.top, b.width, b.height);

						//		if (!map[x][y][0]->intersects(a))
						//		{
						//			return;
						//		}
						//	}
						//}


					// Right and Left
					if (entity->movement_component->GetVelocity().x != 0 && entity->movement_component->GetVelocity().y == 0)
					{
						entity->movement_component->StopVelocityX();
						entity->SetPosition(entity->hitbox_component->last_pos.left, entity->GetPosition().y);

					}
					// Down and Up
					 else if (entity->movement_component->GetVelocity().y != 0 && entity->movement_component->GetVelocity().x == 0)
					{
						entity->movement_component->StopVelocityY();
						entity->SetPosition(entity->GetPosition().x, entity->hitbox_component->last_pos.top);
					}
					
					

					else if (entity->movement_component->GetVelocity().y > 0 && entity->movement_component->GetVelocity().x > 0)
					{
						sf::FloatRect b = entity->GetHitboxBounds();
						sf::FloatRect a(b.left + 1, b.top, b.width, b.height);

						// Right
						if (map[x][y][0]->intersects(a))
						{
							entity->movement_component->StopVelocityX();
							entity->SetPosition(entity->hitbox_component->last_pos.left, entity->GetPosition().y);
							//return;
						}

						b = entity->GetHitboxBounds();
						a.left = b.left;
						a.top += 1;

						if (map[x][y][0]->intersects(a))
						{
							entity->movement_component->StopVelocityY();
							entity->SetPosition(entity->GetPosition().x, entity->hitbox_component->last_pos.top);
							return;
						}

					}



					else if (entity->movement_component->GetVelocity().y > 0 && entity->movement_component->GetVelocity().x < 0)
					{
						sf::FloatRect b = entity->GetHitboxBounds();
						sf::FloatRect a(b.left - 1, b.top, b.width, b.height);

						// Right
						if (map[x][y][0]->intersects(a))
						{
							entity->movement_component->StopVelocityX();
							entity->SetPosition(entity->hitbox_component->last_pos.left, entity->GetPosition().y);
							//return;
						}

						b = entity->GetHitboxBounds();
						a.left = b.left;
						a.top += 1;

						if (map[x][y][0]->intersects(a))
						{
							entity->movement_component->StopVelocityY();
							entity->SetPosition(entity->GetPosition().x, entity->hitbox_component->last_pos.top);
							 return;
						}

					}



					else if (entity->movement_component->GetVelocity().y < 0 && entity->movement_component->GetVelocity().x < 0)
					{
						sf::FloatRect b = entity->GetHitboxBounds();
						sf::FloatRect a(b.left - 1, b.top, b.width, b.height);
						// Right
						if (map[x][y][0]->intersects(a))
						{
							entity->movement_component->StopVelocityX();
							entity->SetPosition(entity->hitbox_component->last_pos.left, entity->GetPosition().y);
							//return;
						}

						b = entity->GetHitboxBounds();
						a.left = b.left;
						a.top -= 1;

						if (map[x][y][0]->intersects(a))
						{
							entity->movement_component->StopVelocityY();
							entity->SetPosition(entity->GetPosition().x, entity->hitbox_component->last_pos.top);
							return;
						}

					}

					else if (entity->movement_component->GetVelocity().y < 0 && entity->movement_component->GetVelocity().x > 0)
					{
						sf::FloatRect b = entity->GetHitboxBounds();
						sf::FloatRect a(b.left + 1, b.top, b.width, b.height);

						// Right
						if (map[x][y][0]->intersects(a))
						{
							entity->movement_component->StopVelocityX();
							entity->SetPosition(entity->hitbox_component->last_pos.left, entity->GetPosition().y);
							//return;
						}

						b = entity->GetHitboxBounds();
						a.left = b.left;
						a.top -= 1;

						if (map[x][y][0]->intersects(a))
						{
							entity->movement_component->StopVelocityY();
							entity->SetPosition(entity->GetPosition().x, entity->hitbox_component->last_pos.top);
							return;
						}

					}

					


				
					

					


				


				



				//	// bottom collision (ENTITY BOTTOM !!)
				//	if (player_bounds.top < wall_bounds.top
				//		&& player_bounds.top + player_bounds.height > wall_bounds.top /*+ wall_bounds.height*/
				///*		&& player_bounds.left < wall_bounds.left + wall_bounds.width
				//		&& player_bounds.left + player_bounds.width > wall_bounds.left*/)
				//	{
				//		entity->movement_component->StopVelocityY();
				//		entity->SetPosition(entity->GetPosition().x, entity->hitbox_component->last_pos.top);
				//	}	

				//	// top
				//	if (player_bounds.top > wall_bounds.top
				//		&& player_bounds.top + player_bounds.height > wall_bounds.top /*+ wall_bounds.height*/
				//		/*&& player_bounds.left < wall_bounds.left + wall_bounds.width
				//		&& player_bounds.left + player_bounds.width > wall_bounds.left*/)
				//	{
				//		entity->movement_component->StopVelocityY();
				//		entity->SetPosition(entity->GetPosition().x, entity->hitbox_component->last_pos.top);
				//	}

				//	// left
				//	if (/*player_bounds.top < wall_bounds.top
				//		&& player_bounds.top + player_bounds.height < wall_bounds.top + wall_bounds.height
				//		 player_bounds.left < wall_bounds.left + wall_bounds.width
				//		&& player_bounds.left + player_bounds.width > wall_bounds.left*/
				//		player_bounds.left < wall_bounds.left
				//		&& player_bounds.left + player_bounds.width> wall_bounds.left)
				//	{
				//		entity->movement_component->StopVelocityX();
				//		entity->SetPosition(entity->hitbox_component->last_pos.left, entity->GetPosition().y);
				//	}

				//	// right
				//	if (/*player_bounds.top < wall_bounds.top
				//		&& player_bounds.top + player_bounds.height < wall_bounds.top + wall_bounds.height
				//		 player_bounds.left < wall_bounds.left + wall_bounds.width
				//		&& player_bounds.left + player_bounds.width > wall_bounds.left*/
				//		player_bounds.left > wall_bounds.left
				//		&& player_bounds.left < wall_bounds.left + wall_bounds.width)
				//	{
				//		entity->movement_component->StopVelocityX();
				//		entity->SetPosition(entity->hitbox_component->last_pos.left, entity->GetPosition().y);
				//	}


					////// left
					////if (player_bounds.left > wall_bounds.left
					////	&& player_bounds.left + player_bounds.width > wall_bounds.left+ wall_bounds.width
					////	&& player_bounds.top < wall_bounds.top + wall_bounds.height
					////	&& player_bounds.top + player_bounds.height > wall_bounds.top
					////	)
					////{
					////	entity->SetPosition(entity->hitbox_component->last_pos.left, entity->GetPosition().y);
					////	entity->movement_component->StopVelocityX();
					////}
					////
					////// right
					////if (player_bounds.left < wall_bounds.left
					////	&& player_bounds.left + player_bounds.width < wall_bounds.left+ wall_bounds.width
					////	&& player_bounds.top < wall_bounds.top + wall_bounds.height
					////	&& player_bounds.top + player_bounds.height > wall_bounds.top
					////	)
					////{
					////	entity->SetPosition(entity->hitbox_component->last_pos.left, entity->GetPosition().y);
					////	entity->movement_component->StopVelocityX();
					////}	
					////


				}
			}
		}
	}
}
