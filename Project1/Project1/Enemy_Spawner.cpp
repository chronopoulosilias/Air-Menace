#include "Enemy_Spawner.h"
#include "Level.h"
#include"gamestate.h"
#include"Bomber.h"
#include "Kamikazi.h" 
#include "Battleship.h"
#include "sgg/graphics.h"
#include "turning_fighter.h"
#include "Submarine.h"

void Enemy_Spawner::spawn_submarine(float pos, float time)
{
	Enemy* enemy = new Submarine("Fighter", pos, time);
	GameState::getInstance()->get_current_level()->get_enemies().push_back(enemy);
}

void Enemy_Spawner::spawn_fighter(float pos, float time)
{
	
	Enemy* enemy = new Fighter("Fighter", pos,time);	
	GameState::getInstance()->get_current_level()->get_enemies().push_back(enemy);
	
	
}

void Enemy_Spawner::spawn_turning_fighter(float pos, float time)
{
	Enemy* enemy = new turning_fighter("g", pos, time);
	GameState::getInstance()->get_current_level()->get_enemies().push_back(enemy);
}

void Enemy_Spawner::spawn_bomber(float pos, float time)
{
	Enemy* enemy = new Bomber("Bomber", pos, time);
	GameState::getInstance()->get_current_level()->get_enemies().push_back(enemy);
}

void Enemy_Spawner::spawn_kamikazi(float pos, float time)
{
	Enemy* enemy = new Kamikazi("Kamikazi", pos, time);
	GameState::getInstance()->get_current_level()->get_enemies().push_back(enemy);
}

void Enemy_Spawner::spawn_battleship(float pos, float time)
{
	Enemy* enemy = new Battleship("Battleship", pos, time);
	GameState::getInstance()->get_current_level()->get_enemies().push_back(enemy);
}

void Enemy_Spawner::fighter_wave(float time)
{
	spawn_fighter(0.1f, time);
	spawn_fighter(0.5f, time);
	spawn_fighter(0.9f, time);
}

void Enemy_Spawner::bomber_wave(float time)
{
	spawn_bomber(0.3f, time);
	spawn_bomber(0.7f, time);

}

void Enemy_Spawner::kamikazi_wave(float time)
{
	spawn_kamikazi(0.25f, time);
	spawn_kamikazi(0.5f, time);
	spawn_kamikazi(0.75f, time);
}

void Enemy_Spawner::kamikazi_wave_flanks(float time)
{
	spawn_kamikazi(0.05f, time);
	spawn_kamikazi(0.95f, time);
}

void Enemy_Spawner::fighter_left_wave(float time)
{
	spawn_fighter(0.1f, time);
	spawn_fighter(0.25f, time);
	spawn_fighter(0.4f, time);
}

void Enemy_Spawner::fighter_right_wave(float time)
{
	spawn_fighter(0.6f, time);
	spawn_fighter(0.75f, time);
	spawn_fighter(0.9f, time);
}

void Enemy_Spawner::fill_level_enemies(int level_index)
{
	switch (level_index) {
	case 1:
		spawn_submarine(0.5f, 1.0f);
		spawn_turning_fighter(0.2f, 3.0f);
		spawn_turning_fighter(0.8f, 3.0f);
		fighter_wave(5.0f);
		bomber_wave(8.0f);
		fighter_left_wave(11.0f);
		fighter_right_wave(13.0f);
		kamikazi_wave_flanks(14.0f);
		break;
	case 2:
		kamikazi_wave(3.0f);
		fighter_left_wave(5.0f);
		fighter_right_wave(7.0f);
		kamikazi_wave_flanks(9.0f);
		bomber_wave(11.0f);
		fighter_wave(13.0f);
		bomber_wave(15.0f);
		kamikazi_wave_flanks(17.0f);
		break;
	case 3:
		fighter_wave(5.0f);
		bomber_wave(8.0f);
		fighter_left_wave(11.0f);
		fighter_right_wave(13.0f);
		kamikazi_wave_flanks(14.0f);
		spawn_battleship(0.5f,16.0f);
		break;
	case 4:
		kamikazi_wave(3.0f);
		fighter_left_wave(5.0f);
		fighter_right_wave(7.0f);
		kamikazi_wave_flanks(9.0f);
		bomber_wave(11.0f);
		fighter_wave(13.0f);
		bomber_wave(15.0f);
		kamikazi_wave_flanks(17.0f);
		fighter_right_wave(18.0f);
		fighter_left_wave(19.0f);
		bomber_wave(20.0f);



		break;



	}

}


