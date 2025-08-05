#pragma once
#include "Enemy.h"
#include "Fighter.h"
#include "Gun.h"


class Battleship : public Enemy {
	/*Helper variables for the battleship to move left and right, x_directions gets only 1 nad -1 for right or left, and position_set for when to start moving just on the x axis*/
	float x_direction=1.0f;
	bool position_set = false;

	/*The battleship has tow guns*/
	Gun* gun1 = nullptr; 
	Gun* gun2 = nullptr;

public:
	
	Battleship(const std::string& name, const float& potision,  float generation_time);

	~Battleship();

	void update(float dt);
	void init();
	void draw();
	void enemy_fire();
	void plane_crashed();
};
