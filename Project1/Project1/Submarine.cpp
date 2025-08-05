#include "Submarine.h"
#include "gamestate.h"

Submarine::Submarine(const std::string& name, const float& potision, float generation_time) : Enemy(name, potision, generation_time)
{
    gun1 = new Gun("gun1", potision, generation_time, this); gun1->set_fire_velocity(2.0f); gun1->set_enemy_time_reloading(2000.0f);
    gun2 = new Gun("gun2", potision, generation_time, this); gun1->set_fire_velocity(4.0f); gun1->set_enemy_time_reloading(4000.0f);

}




void Submarine::init(){
    health_points = 25;
    m_height = 1.15f;
    m_width = 0.25f;
    enemy_velocity = 0.45f;
    points = 200;
    enemy_time_reloading = 2000.0f;
    fire_velocity = 2.0f;


	Enemy::init();
	m_brush_enemy.texture = m_state->getFullAssetPath("Submarine.png");

    if (gun1) {
        gun1->init();
    }
    if (gun2) {
        gun2->init();
    }

}

void Submarine::draw() {


    Enemy::draw();
    if (gun1) {
        gun1->draw();
    }
    if (gun2) {
        gun2->draw();
    }


}

void Submarine::update(float dt) {
    if (turn_on()) {
        float delta_time = dt / 1000.0f;
        m_pos_y += sin(angle) * enemy_velocity * delta_time;
        m_pos_x += cos(angle) * enemy_velocity * delta_time;
        switch (phase) {
            
        case 1:
            angle = 3.14f / 2;
            if (m_pos_y > m_state->getCanvasHeight() * 0.3f) {
                phase = 2;
            }
            break;
        case 2:
            angle = 2*3.14f;
            if (m_pos_x > 4.5f) {
                phase = 3;
            }
            break;

        case 3:
            angle = 3*3.14f /4;
            if (m_pos_y > 3.5f) {
                phase = 4;
            }
            break;
        case 4:
            angle = 1.25 * 3.14f;
            if (m_pos_x < 1.5f) {
                phase = 5;
            }
            break;
        case 5:
            angle = 1.75 * 3.14f;
            if (m_pos_y < 0.5f) {
                phase = 1;
            }
            break;
        }

        if (gun1) {
            gun1->update(dt);
        }
        if (gun2) {
            gun2->update(dt);
        }
        
    }


}

void Submarine::enemy_fire() {








}

Submarine::~Submarine()
{
    if (gun1) {
        delete gun1;
    }
    if (gun2) {
        delete gun2;
    }

}
