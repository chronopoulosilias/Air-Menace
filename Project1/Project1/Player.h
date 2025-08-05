#pragma once
#include "GameObject.h"
#include "box.h"
#include "sgg/graphics.h"




class Player : public GameObject, public Box{
	
	graphics::Brush m_brush_player;	/*Player Brush*/
	graphics::Brush m_brush_player_debugging;	/*Player Brush Debugging*/

	const float fire_velocity = 3.0f;	/*Players fire velocity*/
	const float player_velocity = 2.0f;	/*Players velocity*/
	int health_points=10; /*PLayers health points*/

	/*WEAPON AND FIRING*/
    float main_weapon_time_reloading = 500.0f;
	const float secondary_weapon_time_reloading = 2000.0f;
	bool main_weapon_equiped = true;
	bool secondary_weapon_equiped = false;

	const float time_to_change_weapon = 2000.0f;

	float time_change_weapons = 0.0f;

	float time_of_shot;

	bool main_weapon_loaded = true;
	bool secondary_weapon_loaded = true;

	/*END_WEAPON AND FIRING*/



	/*powerup vars*/
	bool shielded = false;
	float time_of_shield;
	const float shield_duration = 5000.000f;

	bool faster_reload = false;
	float timeof_faster_reload;
	const float faster_reload_duration = 5000.000f;

	/*END of powerups*/
public:
	Player(const std::string& name);

	int get_health() { return health_points; }	
	
	void update(float dt);
	void init();
	void draw();
	void hold_in_canvas();
	void lose_health() {
		if (!shielded) {
			health_points--;
			if (health_points < 0) { health_points = 0; }
		}
	
	}
	void player_collided_enemy() { health_points -= 5;	 if (health_points < 0) { health_points = 0; }}	/*if player crashes with another plane loses 5 HP*/
	void plane_crashed();
	void regain_max_health() { health_points = 10; }	/*PLayers regains his max HP=10*/
	void ressurect();

	/*Powerup funcs*/
	void get_shield();
	void check_shield();
	void get_health_boost();
	void get_faster_reload();
	void lose_powerups();
	void check_faster_reload();
	void get_allies();

	/*WEAPON AND FIRING*/
	void change_weapon();
	void player_fire();
};