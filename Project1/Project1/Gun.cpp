#include "Gun.h"
#include "util.h"
#include "gamestate.h"
#include "Battleship.h"
#include "Missle.h"
#include <cmath>
#include <iostream>
Gun::Gun(const std::string& name, const float& potision, float generation_time, class Enemy* battleship) : Enemy(name,potision,generation_time)
{   /*initializes variables from parent Enemy and Box(m_height,m_width)*/
	m_height = 0.2f;
	m_width = 0.125f;
    enemy_time_reloading = 1500.0f;
    fire_velocity = 3.0f;
    health_points = 5;

    /*Initializes its pointer and orientation*/
    this->battleship = battleship;
    orientation = 3.14f;
}

void Gun::update(float dt)
{   /*The guns follow the battleship and after finding their agnle,fire*/
    m_pos_x = battleship->m_pos_x;
    if (m_name == "gun1") {
        m_pos_y = battleship->m_pos_y + 0.4f;
    }
    else { m_pos_y = battleship->m_pos_y - 0.3f; }
    find_angle();
    enemy_fire();
}

void Gun::init()
{   /*Makes the guns start at the coordinates of the battleship with a small diffrence on the y axis*/
    m_pos_x = battleship->m_pos_x ;
    if (m_name == "gun1") {
        m_pos_y = battleship->m_pos_y + 0.4f;
    }
    else{ m_pos_y = battleship->m_pos_y - 0.3f; }

    Enemy::init();
    m_brush_enemy.texture = m_state->getFullAssetPath("Gun.png");
}

void Gun::draw()
{   /*Convert the angle to degrees*/
    
        float degrees = -angle * 180 / 3.14f + 90.0f; /*+90f because of the way the png is set to look down*/
        graphics::setOrientation(degrees);
    /*Change the agnle of drwaing so the gun always is tagreting at the player*/
    Enemy::draw();
    graphics::resetPose(); /*Resets pose*/
}

void Gun::find_angle()
{
    /*Find the angle created by the line with point1 the coordinates of the gun and point2 the coordinates of the player,and the (0,0) point in the canvas*/
    float x1 = ((m_state->getPlayer()->m_pos_y -m_pos_y)) / (m_state->getPlayer()->m_pos_x - m_pos_x);
    angle = (atan((x1)));
    /*if the player has a lower x coordinate than the gun then we add 3.14f to the angle */
    if (m_pos_x > m_state->getPlayer()->m_pos_x) { angle += 3.14f; }

}

void Gun::enemy_fire()
{
   
        /*if the gun is loaded, it  creates a new missle and gives it to the current level beacuse even if the gun gets deleted its fire must continue*/
        if (gun_loaded(enemy_time_reloading)) {
            Missle* missle = new Missle(m_pos_x, m_pos_y, angle, fire_velocity);
            m_state->get_current_level()->enemies_fire.push_back(missle);
        }
    
}
