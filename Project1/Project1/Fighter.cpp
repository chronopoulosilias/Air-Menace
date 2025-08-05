#include "Fighter.h"
#include "GameObject.h"
#include "gamestate.h"
#include "util.h"
#include "Fire.h"
#include "Level.h"


Fighter::Fighter(const std::string& name,const float& potision, float generation_time) : Enemy(name,potision,generation_time)
{   /*initializes variables from parent Enemy and Box(m_height,m_width)*/
    health_points = 1;
    m_height = 0.3f;
    m_width = 0.3f;
    enemy_velocity = 0.8f;
    points = 10;
    enemy_time_reloading = 2000.0f;
    fire_velocity = 2.0f;
}

void Fighter::update(float dt)
{

    Enemy::update(dt);
    
}

void Fighter::init()
{
    Enemy::init();
    m_brush_enemy.texture = m_state->getFullAssetPath("EnemyPlane2.png");

       
}

void Fighter::draw()
{
    Enemy::draw();
}

void Fighter::enemy_fire()
{
    
    /*if the gun is loaded, it  creates a new fire and gives it to the current level beacuse even if the enemy gets deleted its fire must continue*/
    if (gun_loaded(enemy_time_reloading)) {
        Fire* fire = new Fire(m_pos_x, m_pos_y, 3.14f / 2, fire_velocity);
        m_state->get_current_level()->enemies_fire.push_back(fire);
    }
}

