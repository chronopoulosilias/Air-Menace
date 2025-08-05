#include "explosion.h"
#include "gamestate.h"

explotion::explotion(float pos_x, float pos_y, float width, float height) 
{	/*Takes the coordinates of the explotion which are usually the coords of the enemy and width and height of the explotion which are again alligned to how big the plane is*/
	this->m_pos_x = pos_x;
	this->m_pos_y = pos_y;
	this->m_width = width;
	this->m_height = height;
	
	/*init*/
	this->init();
	/*The time for a sprite to change*/
	
	/*Time of spawn of the explotion*/
	spawn_time = graphics::getGlobalTime();
	counter_time_change = time_of_sprite_change;
}

void explotion::update(float dt)
{	
	/*Checks if the time has passed (time_of_sprite_change) from the last time we changed it and if yes change the sprite*/
	if (sprite_change < 5 && graphics::getGlobalTime() - spawn_time > counter_time_change) {
		sprite_change++;
		counter_time_change += time_of_sprite_change;
	}
	/*if s==5 we have reached the final sprite so we set the exlpoton unactive*/
	if (sprite_change == 5 && graphics::getGlobalTime() - spawn_time > counter_time_change){
		this->setActive(false);
	}

}

void explotion::init()
{	/*Loads the sprites*/
	explotion_sprites.push_back(m_state->getFullAssetPath("explosion0.png"));
	explotion_sprites.push_back(m_state->getFullAssetPath("explosion1.png"));
	explotion_sprites.push_back(m_state->getFullAssetPath("explosion2.png"));
	explotion_sprites.push_back(m_state->getFullAssetPath("explosion3.png"));
	explotion_sprites.push_back(m_state->getFullAssetPath("explosion4.png"));
	explotion_sprites.push_back(m_state->getFullAssetPath("explosion5.png"));

	explotion_brush.fill_opacity = 1.0f;
	explotion_brush.outline_opacity = 0.0f;
	
	graphics::playSound(m_state->getFullAssetPath("explosions.mp3"), 0.05f);

}

void explotion::draw()
{
	/*Draw*/
	explotion_brush.texture = explotion_sprites[sprite_change];
	graphics::drawRect(m_pos_x, m_pos_y, m_width, m_height, explotion_brush);
}
