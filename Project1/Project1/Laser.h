#pragma once
#include "Projectile.h"


class Laser : public Projectile {

	float spawn_time;
	const float expire_time = 700.0f;

public:
	Laser(float x, float y, float direction, const float& velocity);


	void update(float dt);
	void init();
	void draw();





};