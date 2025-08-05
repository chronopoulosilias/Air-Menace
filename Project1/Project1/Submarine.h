#pragma once
#include "Enemy.h"
#include "Gun.h"


class Submarine : public Enemy {

	Gun* gun1 = nullptr;
	Gun* gun2 = nullptr;

	bool lost_guns = false;
	bool underwater = false;
	int phase = 1;

	float angle = 3.14f/2;

public:
	Submarine(const std::string& name, const float& potision, float generation_time);
	void init();
	void draw();
	void update(float dt);
	void enemy_fire();
	~Submarine();











};








