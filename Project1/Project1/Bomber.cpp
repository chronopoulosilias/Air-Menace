#include "Bomber.h"
#include "GameObject.h"
#include "gamestate.h"
#include "util.h"
#include "Fire.h"
#include "Level.h"

Bomber::Bomber(const std::string& name, const float& potision, float generation_time) : Enemy(name,potision,generation_time)
{   /*initializes variables from parent Enemy and Box(m_height,m_width)*/
    health_points = 2;
    m_height = 0.5f;
    m_width = 0.5f;
    points = 20;
    enemy_velocity = 0.5f;
    enemy_time_reloading = 1000.0f;
    fire_velocity = 2.5f;
}

void Bomber::update(float dt)
{
    Enemy::update(dt);

}

void Bomber::init()
{
    Enemy::init();
    m_brush_enemy.texture = m_state->getFullAssetPath("EnemyPlane1.png");
}

void Bomber::draw()
{
    Enemy::draw();
}

void Bomber::enemy_fire()
{
    /*if the gun is loaded, it  creates 2 new fire and gives it to the current level beacuse even if the enemy gets deleted its fires must continue*/
    if (gun_loaded(enemy_time_reloading)) {
        Fire* fire1 = new Fire(m_pos_x - 0.1f, m_pos_y, 3.14f / 2, fire_velocity);
        Fire* fire2 = new Fire(m_pos_x + 0.1f, m_pos_y, 3.14f / 2, fire_velocity);
        m_state->get_current_level()->enemies_fire.push_back(fire1);
        m_state->get_current_level()->enemies_fire.push_back(fire2);
    }
}