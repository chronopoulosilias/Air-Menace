#include "Enemy.h"
#include "gamestate.h"
#include "util.h"
#include <iostream>
#include "Level.h"
#include "explosion.h"
#include "Powerup.h"
#include "allied.h"

Enemy::Enemy(const std::string& name, const float& potision,  float generation_time) : GameObject(name)
{
    this->potision = potision; 
    this->generation_time = generation_time;
    
}

void Enemy::update(float dt)
{   /*We get the time now in the level(each level has its own time),and if time now is bigger than the generation_time,the enemy
    starts moving in the y axis,fires and lastrly we check if it is out_of_boundaries or it has crashed*/
    if (turn_on()) {
        float delta_time = dt / 1000.0f;
        m_pos_y += enemy_velocity * delta_time;
        enemy_fire();

        enemy_out_of_boundaries();
        plane_crashed();
    }
    
}

void Enemy::init()
{	
    /*Initial placement of enemy using position */
    m_pos_x = m_state->getCanvasWidth() * potision;
    m_pos_y = m_state->getCanvasHeight() * 0.1f - 2.0f;

    /*Brush*/
    m_brush_enemy.fill_opacity = 1.0f;
    m_brush_enemy.outline_opacity = 0.0f;
    /*Debugging Brush*/
    m_brush_enemy_debugging.fill_opacity = 0.1f;
    m_brush_enemy_debugging.outline_opacity = 1.0f;
    SETCOLOR(m_brush_enemy_debugging.fill_color, 0.1f, 1.0f, 0.1f;)

}

void Enemy::draw()
{   /*Draw*/
    graphics::drawRect(m_pos_x, m_pos_y,
        m_width, m_height, m_brush_enemy);
    /*Debugging draw*/
    if (m_state->m_debugging) {
        graphics::drawRect(m_pos_x, m_pos_y,
            m_width, m_height, m_brush_enemy_debugging);
    }

}

void Enemy::plane_crashed()
{   
    /*if health points gets zero we add the enemy points to the total score of the game,
    then make the enemy unactive so it will get deleted and create an exlpotion that we pass on the current level*/
    if (health_points == 0) { 
        m_state->get_total_score() += points;
        this->m_active = false;
        explotion* ex = new explotion(m_pos_x, m_pos_y, m_width, m_height);
        m_state->get_current_level()->explotions.push_back(ex);
        spawn_powerup();
       
       
    }
}

void Enemy::enemy_fire()
{


}

void Enemy::enemy_out_of_boundaries()
{   /*if the enemy has passed for the canvas and has to been killed by the player it is set unactive so it can be deleted*/
    if (m_pos_y > m_state->getCanvasHeight() * 1.1f) {
        this->m_active = false;
    }
}


bool Enemy::gun_loaded(float enemy_time_reloading)
{   /*Reload method: If the gun is loaded,we make it unloaded and get a time_of_shot,while the gun is not loaded we check if the time now minus the last time_of_shot is bigger than
    they enemy_time_reloading so we set gun_reloaded to true again */
    if (gun_reloaded) {
        gun_reloaded = false;
        time_of_shot = graphics::getGlobalTime();
    }
    if (graphics::getGlobalTime() - time_of_shot > enemy_time_reloading) {
        gun_reloaded = true;
    }
    if (gun_reloaded) { return true; }
    else { return false; }
}

bool Enemy::turn_on()
{
    float time = graphics::getGlobalTime() / 1000.0f - m_state->get_current_level()->get_level_spawn_time() / 1000.0f;
    if (time > generation_time) {
        return true;
    }
    else {
        return false;
    }
}

void Enemy::spawn_powerup()
{
    int possiblity = rand() % 101;
    if (possiblity <= 30) {
        Powerup* ex = new Powerup(m_pos_x, m_pos_y, 3.14f / 2, 1.0f);
        m_state->get_current_level()->powerups.push_back(ex);
    }


}





