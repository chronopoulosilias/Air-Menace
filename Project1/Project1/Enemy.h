#pragma once
#include "GameObject.h"
#include "box.h"
#include "sgg/graphics.h"



class Enemy : public GameObject,public Box {
protected:
	graphics::Brush m_brush_enemy; /* Brush of enemy*/
	graphics::Brush m_brush_enemy_debugging;	/* Brush of enemy in debugging*/

	 float fire_velocity; /* Speed of enemy's fire */
	 float potision = NULL;	/* Position on the x axis for enemy spawn */
	 float generation_time; /* Time of enemy spawn */
	 int health_points;	/* Health points */
	 float enemy_velocity;	/* Enemy's speed */
	 int points;	/* Enemy's score points  */

	 
	 float enemy_time_reloading; /* Enemy's time to reload */
	 bool gun_reloaded = true; 
	 float time_of_shot;
	 
	 
	 

public:
	Enemy(const std::string& name, const float& potision,float generation_time);

	void update(float dt); 
	void init();
	void draw();
	void lose_health() { health_points--; }; /* Substacts 1 health point from the enemy*/
	void plane_crashed();
	virtual void enemy_fire();
	void enemy_out_of_boundaries();
	bool gun_loaded(float enemy_time_reloading);

	void set_fire_velocity(float new_fire_velocity) { fire_velocity = new_fire_velocity; }
	void set_enemy_time_reloading(float new_enemy_time_reloading) { enemy_time_reloading = new_enemy_time_reloading; }

	bool turn_on();

	void spawn_powerup();
};
