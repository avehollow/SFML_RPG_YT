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
#include <string>
#include <queue>

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;

using std::make_unique;
using std::make_shared;
using std::string;
using std::vector;
using std::map;
using std::stack;
using std::queue;
using std::pair;
using std::to_string;


//This pointer does not manage memory; Dont try to delete ! This pointer used only for access to data
#define ACCESS_POINTER 

class Entity
{
private:

protected:
	ACCESS_POINTER sf::Sprite*  sprite  = nullptr; 
	ACCESS_POINTER sf::Texture* texture = nullptr;
	float movement_speed = 100.0f;

public:
	virtual const sf::Vector2f& GetPosition();
	virtual void				SetPosition(const float x, const float y);
	virtual void				move(const float& frame_time, float dir_x, float dir_y);

public:
	Entity();
	virtual ~Entity();

	virtual void Update(const float& frame_time)		    ;// = 0;
	virtual void Render(sf::RenderTarget* target = nullptr) ;// = 0;

};

