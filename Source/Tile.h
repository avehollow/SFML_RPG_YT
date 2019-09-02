#pragma once

class Tile
{
private:
	sf::RectangleShape shape;

public:
	Tile(float pos_x, float pos_y, size_t size);
	virtual ~Tile();

	void Update(const float& frame_time);
	void Render(sf::RenderWindow* window) const;
};

