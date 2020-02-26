#include "pch.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(size_t level)
{
}

AttributeComponent::AttributeComponent()
{
}

AttributeComponent::~AttributeComponent()
{
}

void AttributeComponent::CalculateNextExpThreshold()
{
	// wielomian 3 stopnia!! zobacz wykres
	// wykres: (50 / 3) * (x^3 - 6 * x^2) + (x*17) - 12)
	// proponuje e^log e^x
	// ale to dzia³a 
	exp_to_next_level = (50 / 3) * (pow(level + 1, 3) - 6 * pow(level + 1, 2) + ((level + 1) * 17ll) - 12);
}

void AttributeComponent::Update()
{
	srand(time(NULL));
	// It may happen that we get experience on 2 or more level
	// i.e some quest give us 100000000 exp :P
	while (experience >= exp_to_next_level)
	{
		level++;
		experience -= exp_to_next_level;
		attribute_points += 3;

		if (!(level%5))
		{
			//hp_max += (rand()%250) + 250ll;		// random number [250;500]
			hp_bonus += 250ll;
		}
		CalculateNextExpThreshold();
		this->UpdateAttribute();

	}
}

void AttributeComponent::ResetAttribute()
{
	attribute_points = spent_attribute_points;

	strength		= 1;
	vitality		= 1;
	dexterity		= 1;
	intelligence	= 1;
	luck			= 1;


	spent_attribute_points = 0;

	this->UpdateAttribute();
}

void AttributeComponent::AddAttribute(ATTRIBUTE att)
{
	if (attribute_points <= 0) return;
								
	switch (att)
	{
		case STR:
			strength++;
			break;
		case VIT:
			vitality++;
			break;
		case DEX:
			dexterity++;
			break;
		case INT:
			intelligence++;
			break;
		default:
			break;
	}
	spent_attribute_points++;
}

std::string AttributeComponent::DebugPrint() const
{
	std::stringstream ss;
	ss  << "Level:"         << level			   << "\n"
		<< "Experience:"    << experience		   << "\n"
		<< "ExpToNextLvl:"  << exp_to_next_level   << "\n"
		<< "AttributePoint:"<< attribute_points    << "\n"
		<< "Hp_Current:"    << hp_current		   << "\n"
		<< "Press E to gain experience "		   << "\n"
		<< "Press Q to get damage "				   << "\n"
		;
	return ss.str();
}

void AttributeComponent::UpdateAttribute()
{
	hp_max = (vitality * 9ll + strength * 5ll) + 100ll + hp_bonus;
	hp_current = hp_max;

	mana_max = (intelligence * 15ll) + 100ll;
	mana_current = mana_max;

	accuracy = dexterity * 10ll;

	luck = (long long)(vitality + strength  + intelligence + dexterity) ;

}
