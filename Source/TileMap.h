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

	// HLOG The map should manage the texture_sheet on its own
	sf::Texture* texture_sheet;



	// Culling
	int fromX = 0;
	int toX   = 0;
	int fromY = 0;
	int toY   = 0;
	int layer = 0;

private:
	void CreateMap();

public:
	// HLOG The map should manage the texture_sheet on its own
	TileMap(sf::Texture* texture_sheet, class StateData* sd = nullptr);
	~TileMap();

	void AddTile(int pos_x, int pos_y, int pos_z, sf::IntRect rect, bool collision = false);
	void RemoveTile(int pos_x, int pos_y, int pos_z);

	void SaveToFile();
	void LoadFromFile();

	void Update(const float& frame_time, bool bShowCollision = false);
	void Render(sf::RenderWindow* window, class Entity* entity);


	void SetTextureSheet(sf::Texture* texture)
	{
		texture_sheet = texture;
	}

	void UpdateCollision(class Entity* entity);
};

