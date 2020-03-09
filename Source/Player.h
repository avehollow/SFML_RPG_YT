#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
	bool atack = false;
public:

	Player(float posX, float posY, sf::Sprite* sprite, sf::Texture* texture);
	virtual ~Player();



	size_t& level()				  { return attribute_component->level;  }
	size_t& experience()		  { return attribute_component->experience; }
	size_t& exp_to_next_level()   { return attribute_component->exp_to_next_level; }
	size_t& attribute_points()    { return attribute_component->attribute_points; }


	int& strength()				  { return attribute_component->strength; }
	int& vitality()				  { return attribute_component->vitality; }
	int& dexterity()			  { return attribute_component->dexterity; } // Zwinnoœæ
	int& intelligence()			  { return attribute_component->intelligence; }


	long long& hp_current()		  { return attribute_component->hp_current; }
	long long& hp_max()			  { return attribute_component->hp_max; }
	

	long long& mana_current()	  { return attribute_component->mana_current; }
	long long& mana_max()		  { return attribute_component->mana_max; }

	long long& damage_min()		  { return attribute_component->damage_min; }
	long long& damage_max()		  { return attribute_component->damage_max; }

	long long& accuracy()		  { return attribute_component->accuracy; } // Precyzja
	long long& defence()		  { return attribute_component->defence;  }
	long long& luck()			  { return attribute_component->luck; }


	void UpdateAnimation(const float& frame_time);
	void Update(const float& frame_time) override;
	void Render(sf::RenderWindow* window) override;
};

