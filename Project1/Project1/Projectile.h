#pragma once
#include "GameObject.h"
#include "box.h"
#include "sgg/graphics.h"


class Projectile : public Box, public GameObject {
protected:
	graphics::Brush m_brush_projectile; /*Fire brush*/
	graphics::Brush m_brush_projectile_debugging;	/*Fire brush in debugging*/
	float velocity = NULL;	/*velocity of fire*/
	float direction = NULL;	/*direction of fire*/


public:
	Projectile(float x, float y, float direction,const float& velocity);

	void check_if_inside_canvas(float dt);
	void update(float dt);
	void init();
	void draw();





};