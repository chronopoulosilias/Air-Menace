#pragma once
#include "Projectile.h"



class Missle : public  Projectile{

public:
	Missle(float x, float y, float direction,const float& velocity);
	void update(float dt);
	void init();
	void draw();


};