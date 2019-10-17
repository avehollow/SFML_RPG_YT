#pragma once



class Tile
{
public:
	enum Type : uint8_t
	{
		DEFAULT  = 0,
		DAMAGING = 1,
	};


//private:
public:
	sf::Texture* texture;
	sf::RectangleShape shape;
	bool  bCollision;
	short type;

public:
	Tile(float pos_x, float pos_y, size_t size);
	virtual ~Tile();

	void Update(const float& frame_time, bool bShowCollision = false);
	void Render(sf::RenderWindow* window) const;


	bool intersects(const sf::FloatRect bounds) const;
	const std::string PlaceTileInfoToString();
};

