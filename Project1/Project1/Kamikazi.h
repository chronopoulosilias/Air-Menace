#pragma once
#include "Enemy.h"


class Kamikazi : public Enemy {

	
public:
	Kamikazi(const std::string& name, const float& potision, float generation_time);

	void update(float dt);
	void init();
	void draw();
	void enemy_fire();
};
