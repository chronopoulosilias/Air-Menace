#include "Fire.h"
#include "gamestate.h"
#include "Player.h"
#include "util.h"
#include "cmath"
#include "Projectile.h"

Fire::Fire(float x,float y,float direction,const float& velocity ) : Projectile(x,y,direction,velocity)
{	
	
	/*Initializes box variables*/
	m_height = 0.08;
	m_width = 0.08f;
	this->init();
	
}



void Fire::update(float dt)
{	
	Projectile::update(dt);

	
}

void Fire::init()
{	
	m_brush_projectile.texture = m_state->getFullAssetPath("bullet.png");
	Projectile::init();
	
	

	
}

void Fire::draw()
{	/*Draw*/
	Projectile::draw();

}



