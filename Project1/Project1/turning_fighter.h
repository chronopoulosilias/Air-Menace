#pragma once
#include "Enemy.h"

class turning_fighter : public Enemy {


	float angle = 3.14/2;
	int phase = 1;


public:

	turning_fighter(const std::string& name, const float& potision, float generation_time);
	void update(float dt);
	void init();
	void draw();
	void enemy_fire();
	void enemy_out_of_boundaries();
	
};