#pragma once
#include "GameObject.h"
#include "box.h"
#include "sgg/graphics.h"
#include "Player.h"
#include "Projectile.h"

class Fire : public Projectile {
protected:
	

public:
	Fire(float x,float y,float direction,const float& velocity );

	
	void update(float dt);
	void init();
	void draw();


};









