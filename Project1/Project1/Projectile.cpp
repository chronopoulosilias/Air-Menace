#include "Projectile.h"
#include "gamestate.h"
#include "util.h"

Projectile::Projectile(float x, float y, float direction, const float& velocity)
{
	/*Takes its (x,y) coordinates, a direction in rad, a name and velocity of the fire and initializes them*/
	this->velocity = velocity;
	this->m_pos_x = x;
	this->m_pos_y = y;
	this->direction = direction;

	this->init();



}

void Projectile::check_if_inside_canvas(float dt)
{
	/*If a fire is outside of our canvas then we should delete it for memory managment*/
	if (m_pos_y < 0.0f * m_state->getCanvasHeight() + 0.001f) {
		setActive(false);

	}
	if (m_pos_y > 1.0f * m_state->getCanvasHeight() + 0.1f) {
		setActive(false);

	}
	if (m_pos_x < 0.0f * m_state->getCanvasWidth() - 0.1f) {
		setActive(false);

	}
	if (m_pos_x > 1.0f * m_state->getCanvasWidth() + 0.1f) {
		setActive(false);

	}



}

void Projectile::update(float dt)
{
	/*Moves the fire in the y and x axis based on direction which is in rad and time,and also checks if it is still inside our canvas*/
	float delta_time = dt / 1000.0f;
	m_pos_y += sin(direction) * velocity * delta_time;
	m_pos_x += cos(direction) * velocity * delta_time;
	check_if_inside_canvas(dt);
}

void Projectile::init()
{
	/*Brush*/
	m_brush_projectile.fill_opacity = 1.0f;
	m_brush_projectile.outline_opacity = 0.0f;
	/*Debugging brush*/
	m_brush_projectile_debugging.fill_opacity = 0.1f;
	m_brush_projectile_debugging.outline_opacity = 1.0f;
	SETCOLOR(m_brush_projectile_debugging.fill_color, 0.1f, 1.0f, 0.1f;)

}

void Projectile::draw()
{
	/*Draw*/
	graphics::drawRect(m_pos_x, m_pos_y,
		m_height,m_width, m_brush_projectile);
	/*Debugging draw*/
	if (m_state->m_debugging) {
		graphics::drawRect(m_pos_x, m_pos_y,
			m_height, m_width, m_brush_projectile_debugging);
	}
}
