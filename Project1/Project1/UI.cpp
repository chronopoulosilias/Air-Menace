#include "UI.h"
#include "util.h"
#include "gamestate.h"




UI::UI() {

}


void UI::init() {

	score.outline_opacity = 0.0f;
    m_health_brush.outline_opacity = 0.0f;
    SETCOLOR(m_health_brush.fill_color, 1.0f, 0.0f, 0.0f);

    m_heart_brush.outline_opacity = 0.0f;
    m_heart_brush.texture = m_state->getFullAssetPath("heart.png");

}

void UI::draw() {
    /*Health bar*/
    graphics::drawRect(m_state->getCanvasWidth() - 5.8f - ((1.0f - m_state->getPlayer()->get_health()) * 0.04f / 2), m_state->getCanvasHeight() * 0.98f,
        m_state->getPlayer()->get_health() * 0.04f, 0.1f, m_health_brush);
    /*Heart*/
    graphics::drawRect(m_state->getCanvasWidth() - 5.9f, m_state->getCanvasHeight() * 0.98f,
        0.1f, 0.1f, m_heart_brush);
    /*Score*/
    char info[40];
    sprintf_s(info, "Score:%d", m_state->get_total_score());
    graphics::drawText(m_state->getCanvasWidth() * 0.88f, m_state->getCanvasHeight() * 0.99f, 0.15f, info, score);
    /*Level*/
    char info1[40];
    sprintf_s(info1, "Level:%d", m_state->get_current_level()->get_level_index());
    graphics::drawText(m_state->getCanvasWidth() * 0.88f, m_state->getCanvasHeight() * 0.97f, 0.15f, info1, score);


}

void UI::update(float dt) {



}