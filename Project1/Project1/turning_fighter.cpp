#include "turning_fighter.h"
#include "gamestate.h"
#include "util.h"


turning_fighter::turning_fighter(const std::string& name, const float& potision, float generation_time) : Enemy(name, potision, generation_time)
{
	health_points = 1;
	m_height = 0.2f;
	m_width = 0.2f;
	enemy_velocity = 0.8f;
	points = 10;
	enemy_time_reloading = 1500.0f;
	fire_velocity = 2.0f;
}


void turning_fighter::init()
{
	Enemy::init();
	m_brush_enemy.texture = m_state->getFullAssetPath("EnemyPlane2.png");


}


void turning_fighter::draw()
{
	float degrees = -angle * 180 / 3.14f + 90.0f;
	graphics::setOrientation(degrees);
	Enemy::draw();
	graphics::resetPose();

}



void turning_fighter::update(float dt)
{

	if (turn_on()) {
		float delta_time = dt / 1000.0f;
		m_pos_y += sin(angle) * enemy_velocity * delta_time;
		m_pos_x += cos(angle) * enemy_velocity * delta_time;
		switch (phase) {
		case 1:
			if (m_pos_y > m_state->getCanvasHeight() * 0.7f) {
				phase = 2;
			}
			break;
		case 2:
			if (potision >= 0.5f) {
				angle += 0.008f;
				if (angle > 1.5 * 3.14f) { phase = 3; }
			}
			if (potision < 0.5f) {
				angle -= 0.008f;
				if (angle < -3.14f/2) { phase = 3; }
			}
			enemy_fire();
			break;
		case 3:

			enemy_out_of_boundaries();
			break;
		}


	plane_crashed();
	}


}

void turning_fighter::enemy_fire() {
	if (gun_loaded(enemy_time_reloading)) {
		Fire* fire = new Fire(m_pos_x, m_pos_y, 3.14f / 2, fire_velocity);
		Fire* fire1 = new Fire(m_pos_x, m_pos_y, 3.14f / 2 + 0.5f, fire_velocity);
		Fire* fire2 = new Fire(m_pos_x, m_pos_y, 3.14f / 2 - 0.5f, fire_velocity);
		m_state->get_current_level()->enemies_fire.push_back(fire);
		m_state->get_current_level()->enemies_fire.push_back(fire1);
		m_state->get_current_level()->enemies_fire.push_back(fire2);
	}


}

void turning_fighter::enemy_out_of_boundaries() {
	Enemy::enemy_out_of_boundaries();
	if (m_pos_y < -0.1f) {
		this->m_active = false;
	}


}