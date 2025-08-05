#pragma once
#include "GameObject.h"
#include <string>
#include "sgg/graphics.h"
#include "box.h"


class explotion : public GameObject, public Box {

	const float duration_of_explotion = 600.0f; /*The time of the exploton*/
	std::vector<std::string>  explotion_sprites;	/*The sprites of the explotion*/
	graphics::Brush explotion_brush;	/*Brush*/
	
	int sprite_change = 0;
	const float time_of_sprite_change = duration_of_explotion / 5;
	float counter_time_change;
	float spawn_time;
public:
	explotion(float m_pos_x,float m_pos_y,float m_width,float m_height );
	void update(float dt);
	void init();
	void draw();


};