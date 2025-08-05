#include "ally_fighter.h"
#include "gamestate.h"

ally_fighter::ally_fighter(bool left)
{
    this->left = left;
    m_height = 0.2f;
    m_width = 0.2f;
    health_points = 1;
    ally_time_reloading = 3000.0f;
    this->init();

}

void ally_fighter::update(float dt) {

    if (left) {
        m_pos_x = m_state->getPlayer()->m_pos_x + 0.4f;

    }
    else {
        m_pos_x = m_state->getPlayer()->m_pos_x - 0.4f;


    }
    m_pos_y = m_state->getPlayer()->m_pos_y;
    ally_fire();
    plane_crashed();



}

void ally_fighter::init() {

    allied::init();
    m_brush_ally.texture = m_state->getFullAssetPath("ally_fighter.png");




}

void ally_fighter::draw() {

    allied::draw();
    




}