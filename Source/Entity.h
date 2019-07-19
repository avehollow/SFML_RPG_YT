#pragma once

#include "imgui/imgui.h"
#include "imgui-sfml/imgui-SFML.h"
#include "SFML/Graphics.hpp"

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <fstream>

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

using std::make_unique;
using std::string;


class Entity
{
private:

protected:
	sf::RectangleShape shape;
	float movement_speed = 100.0f;

public:
	virtual void move(const float& frame_time, float dir_x, float dir_y);

public:
	Entity();
	virtual ~Entity();

	virtual void Update(const float& frame_time)		   ;// = 0;
	virtual void Render(sf::RenderTarget* window = nullptr);// = 0;

};

