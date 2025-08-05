#pragma once
#include "Projectile.h"
#include "box.h"
#include "sgg/graphics.h"


class Powerup : public Projectile{
protected:
	
	
	bool shield = false;
	bool health_boost = false;
	bool faster_reload = false;
	bool allies = false;
	int pick;

public:
	Powerup(float x, float y, float direction,const float& velocity);

	void update(float dt);
	void init();
	void draw();
	int getpick() { return pick; }




};