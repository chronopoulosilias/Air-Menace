#pragma once
#include "Enemy.h"


class Bomber : public Enemy {

public:
	Bomber(const std::string& name, const float& potision,float generation_time);

	void update(float dt);
	void init();
	void draw();
	void enemy_fire();
};

