#pragma once

enum ATTRIBUTE
{
	STR = 0,
	VIT,
	DEX,
	INT
};


class AttributeComponent
{
public:
	size_t level				= 1;
	size_t experience			= 0;
	size_t exp_to_next_level	= 100;
	size_t attribute_points		= 3;


	int strength				= 1;
	int vitality				= 1;
	int dexterity				= 1;  // Zwinnoœæ
	int intelligence			= 1;


	long long hp_current		= 100;
	long long hp_max			= 100;

	long long mana_current		= 100;
	long long mana_max			= 100;

	long long damage_min		= 1;
	long long damage_max		= 10;

	long long accuracy			= 0; // Precyzja
	long long defence			= 0;
	long long luck				= 0;

public:
	AttributeComponent(size_t level);
	AttributeComponent();
	~AttributeComponent();

	// Threshold - próg
	void CalculateNextExpThreshold(); 
	void Update();
	void ResetAttribute();
	void AddAttribute(ATTRIBUTE att);
	inline void GainExp(int exp) // Wszystkie funkcje z definicja w ciele klasy s¹ inline wiêc nie potrzeba specyfikatora inline ale mniejsza o to :D
	{
		experience += exp;
	}

	std::string DebugPrint()const;

private:
	void UpdateAttribute();

	size_t spent_attribute_points = 0;

};

