#include "Laser.h"
#include "gamestate.h"

Laser::Laser(float x, float y, float direction, const float& velocity) : Projectile(x, y, direction, velocity)
{
	/*Initializes box variables*/
	m_pos_y += -2.5f;
	m_height = 5.0f;
	m_width = 0.10f;
	this->init();
	spawn_time = graphics::getGlobalTime();

}

void Laser::update(float dt)
{
	if (graphics::getGlobalTime() - spawn_time > expire_time) {
		this->setActive(false);
	}
}

void Laser::init()
{
	Projectile::init();
	m_brush_projectile.texture = m_state->getFullAssetPath("blue_laser.png");
}

void Laser::draw()
{
	float degrees = direction * 180 / 3.14f ;
	graphics::setOrientation(degrees);
	Projectile::draw();
	graphics::resetPose();
}
