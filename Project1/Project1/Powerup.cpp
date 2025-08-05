#include "Powerup.h"
#include "gamestate.h"
#include "util.h"
Powerup::Powerup(float x, float y, float direction, const float& velocity) : Projectile(x,y,direction,velocity)
{
	
	/*Initializes box variables*/
	m_height = 0.2f;
	m_width = 0.2f;
	this->init();
}



void Powerup::update(float dt)
{
	Projectile::update(dt);
}

void Powerup::init()
{

	Projectile::init();

	pick = rand() % 4;
	
	if (pick == 0) {
		shield = true;
		m_brush_projectile.texture = m_state->getFullAssetPath("shield.png");
	}
	else if (pick == 1) {
		health_boost = true;
		m_brush_projectile.texture = m_state->getFullAssetPath("heart.png");
	}
	else if (pick == 2) {
		faster_reload = true;
		m_brush_projectile.texture = m_state->getFullAssetPath("faster_reload.png");
	}
	else{
		allies = true;
		m_brush_projectile.texture = m_state->getFullAssetPath("ally_fighter.png");
	}

}

void Powerup::draw()
{
	/*Draw*/
	Projectile::draw();


}
