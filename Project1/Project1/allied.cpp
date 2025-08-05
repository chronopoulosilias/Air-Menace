#include "allied.h"
#include "gamestate.h"
#include "util.h"
#include"gamestate.h"

allied::allied()
{
}


void allied::update(float dt) {



}

void allied::init() {
    /*Brush*/
    m_brush_ally.fill_opacity = 1.0f;
    m_brush_ally.outline_opacity = 0.0f;
    /*Debugging Brush*/
    m_brush_ally_debugging.fill_opacity = 0.1f;
    m_brush_ally_debugging.outline_opacity = 1.0f;
    SETCOLOR(m_brush_ally_debugging.fill_color, 0.1f, 1.0f, 0.1f;)


}


void allied::draw() {
    /*Draw*/
    graphics::drawRect(m_pos_x, m_pos_y,
        m_width, m_height, m_brush_ally);
    /*Debugging draw*/
    if (m_state->m_debugging) {
        graphics::drawRect(m_pos_x, m_pos_y,
            m_width, m_height, m_brush_ally_debugging);
    }


}


void allied::plane_crashed() {
    if (health_points <= 0) {
        this->m_active = false;
        explotion* ex = new explotion(m_pos_x, m_pos_y, m_width, m_height);
        m_state->get_current_level()->explotions.push_back(ex);

    }


}


void allied::ally_fire() {
    if (gun_loaded(ally_time_reloading)) {
        Projectile* fire = new Fire(m_pos_x, m_pos_y, 3 * 3.14f / 2, 3.0f);
        m_state->get_current_level()->players_fire.push_back(fire);
    }


}

bool allied::gun_loaded(float ally_time_reloading) {
    if (gun_reloaded) {
        gun_reloaded = false;
        time_of_shot = graphics::getGlobalTime();
    }
    if (graphics::getGlobalTime() - time_of_shot > ally_time_reloading) {
        gun_reloaded = true;
    }
    if (gun_reloaded) { return true; }
    else { return false; }

}
