#pragma once
#include "GameObject.h"
#include "box.h"
#include "sgg/graphics.h"

class allied : public GameObject, public Box {
protected:
	graphics::Brush m_brush_ally; /* Brush of enemy*/
	graphics::Brush m_brush_ally_debugging;	/* Brush of enemy in debugging*/

	int health_points;	/* Health points */
	float ally_velocity;	/* Enemy's speed */
	


	float ally_time_reloading; /* Enemy's time to reload */
	bool gun_reloaded = true;
	float time_of_shot;


public:
	allied();

	void update(float dt);
	void init();
	void draw();
	void lose_health() { health_points--; }; /* Substacts 1 health point from the enemy*/
	void plane_crashed();
	virtual void ally_fire();
	bool gun_loaded(float ally_time_reloading);








};