#include "Missle.h"
#include "Fire.h"
#include "gamestate.h"

Missle::Missle(float x, float y, float direction,  const float& velocity) : Projectile(x, y, direction,velocity) {
	/*Same as fire but with different box variables*/
	m_height = 0.1f;
	m_width = 0.3f;
	this->init();
	
}

void Missle::update(float dt)
{
	Projectile::update(dt);

}

void Missle::init()
{	
	Projectile::init();
	m_brush_projectile.texture = m_state->getFullAssetPath("missle1.png");
}

void Missle::draw()
{	/*Draws the missle according to the direction in rad which we will convert in dergees and then draw with this orientation and finally resetPose*/
	float degrees = -direction * 180 / 3.14f + 90.0f;
	graphics::setOrientation(degrees);
	Projectile::draw();
	graphics::resetPose();

}
