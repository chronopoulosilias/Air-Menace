#include "Carrier.h"
#include "gamestate.h"

Carrier::Carrier()
{
	m_height = 1.2f;
	m_width = 0.3f;
	health_points = 3;
	ally_velocity = 0.4f;
	this->init();
}



void Carrier::update(float dt) {
	float delta_time = dt / 1000.0f;
	if (m_pos_y > m_state->getCanvasHeight() * 0.9f && potision_set == false) {

		m_pos_y -= ally_velocity * delta_time;
	}
	else { potision_set = true; }

	if (potision_set) {
		if (m_pos_x < m_state->getCanvasWidth() * 0.35f) {
			x_direction = 1.0f;
		}
		else if (m_pos_x > m_state->getCanvasWidth() * 0.85f) {
			x_direction = -1.0f;
		}
		m_pos_x += x_direction * ally_velocity * delta_time;

	}


	plane_crashed();
}

void Carrier::init() {
	allied::init();
	m_brush_ally.texture = m_state->getFullAssetPath("Carrier.png");
	m_pos_x = 3.0f;
	m_pos_y = 7.0f;

}

void Carrier::draw() {

	allied::draw();
}