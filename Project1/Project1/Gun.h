#pragma once
#include "Enemy.h"


class Gun : public Enemy {
	/*The gun has a pointer to the battleship that owns it*/
	class Enemy* battleship;
	/*orienation and angle are useful for turning of the gun*/
	float orientation;
	float angle=0.0f;



public:
	Gun(const std::string& name, const float& potision, float generation_time, class Enemy* battleship);

	void update(float dt);
	void init();
	void draw();
	void enemy_fire();
	void find_angle();
};