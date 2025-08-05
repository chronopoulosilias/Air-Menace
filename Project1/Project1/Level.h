#pragma once
#include "GameObject.h"
#include "sgg/graphics.h"
#include <list>
#include "Fire.h"
#include "Enemy.h"
#include "Fighter.h"
#include "Player.h"
#include "explosion.h"
#include "Powerup.h"
#include "Projectile.h"
#include "ally_fighter.h"
#include "UI.h"

class Level: public GameObject {
protected:
	graphics::Brush m_back_brush;	/*Backround brush*/
	
	UI* level_ui;
	int level_index;
	float level_spawn_time = NULL; /*Time the level is borned*/
	
		/*Enemies of the level*/
	
	
	const float time_of_pause = 3000.0f; /*Time needed to pass or fail the level after a condition of fail or pass has been met*/
	/*Variables for the pass or fail of the level*/
	float time_of_pass=NULL;
	bool level_passed = false;
	float time_of_fail = NULL;
	bool level_failed = false;
	
	bool game_paused = false;

	/*Function that takes a vector of Gameobjects(ancestors) and removes the unactive objects*/
	template <typename T>
	void remove_unactive_objects(std::vector<T*>& vector) {
		std::vector<T*> new_vector;
		for (int i = 0; i < vector.size(); i++) {
			if (vector[i]->isActive() == false) {
				delete vector[i];
			}
			else {
				new_vector.push_back(vector[i]);
			}
		}
		vector = new_vector;
	
	};
	
	


public:
	std::vector<ally_fighter*> m_allies;
	std::vector<Enemy*> m_enemies;
	std::vector<Projectile*> players_fire;	/*Fires of the player*/
	std::vector<Projectile*> enemies_fire;	/*Fires of the Enemies*/
	std::vector<explotion*> explotions;
	std::vector<Powerup*> powerups;	/*Explotions*/
	

	void update(float dt);
	void init();
	void draw();
	
	void spawn_allies();
	virtual void checkcolitions(float dt);
	Level(int level_index);
	int get_level_index() { return level_index; }
	
	bool level_has_passed();
	bool level_has_failed();
	float get_level_spawn_time() { return level_spawn_time; }	/*return the time the level was born*/
	std::vector<Enemy*>& get_enemies() { return m_enemies; }	/*return the enemies of the level by a reference*/
	~Level();
	void pause_game();

	virtual void remove_all_unactive_objects();

	virtual void chech_win_condition();
	virtual void check_defeat_condition();

	virtual void update_gameobjects(float dt);
};