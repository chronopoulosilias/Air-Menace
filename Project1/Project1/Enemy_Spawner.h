#pragma once
#include "Enemy.h"
#include "Level.h"
#include "gamestate.h"


static class Enemy_Spawner {


public:
	void spawn_submarine(float pos, float time);
	void spawn_fighter(float pos,float time);
	void spawn_turning_fighter(float pos, float time);
	void spawn_bomber(float pos, float time);
	void spawn_kamikazi(float pos, float time);
	void spawn_battleship(float pos, float time);

	void fighter_wave(float time);
	void bomber_wave(float time);
	void kamikazi_wave(float time);

	void kamikazi_wave_flanks(float time);
	void fighter_left_wave(float time);
	void fighter_right_wave(float time);

	void fill_level_enemies(int level_index);

};