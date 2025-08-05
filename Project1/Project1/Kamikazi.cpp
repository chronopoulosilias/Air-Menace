#include "Kamikazi.h"
#include "GameObject.h"
#include "gamestate.h"
#include "util.h"
#include "Fire.h"
#include "Level.h"

Kamikazi::Kamikazi(const std::string& name, const float& potision, float generation_time) : Enemy(name,potision,generation_time)
{   
    enemy_velocity = 2.5f;
    health_points = 1;
    m_height = 0.2f;
    m_width = 0.2f;
    points = 15;
	
}

void Kamikazi::update(float dt)
{
    Enemy::update(dt);
}

void Kamikazi::init()
{
    Enemy::init();
    m_brush_enemy.texture = m_state->getFullAssetPath("EnemyPlane3.png");
    
}

void Kamikazi::draw()
{
    Enemy::draw();
}

void Kamikazi::enemy_fire()
{
    /*The kamikazi doesnt fire but just tries to crash onto the player thus the method is empty*/
}
