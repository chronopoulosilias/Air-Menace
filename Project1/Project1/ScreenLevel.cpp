#include "ScreenLevel.h"
#include "gamestate.h"

void ScreenLevel::update(float dt)
{   /*Checks if pass or to pause while PLAYING*/
    if (m_name == "START") {
        m_back_brush.texture = background_images[0];
        if (graphics::getKeyState(graphics::SCANCODE_P)) {
            pass = true;
        }
        if (graphics::getKeyState(graphics::SCANCODE_H)) {
            m_back_brush.texture = m_state->getFullAssetPath("helpscreen.png");
            
        }
        if (graphics::getKeyState(graphics::SCANCODE_Q)) {
            m_back_brush.texture = m_state->getFullAssetPath("STARTSCREEN.png");
        }
    }
    if (m_name == "RETRY") {
        m_back_brush.texture = background_images[1];
        if (graphics::getKeyState(graphics::SCANCODE_R)) {
            pass = true;
        }
    }
    if (m_name == "END") {
        m_back_brush.texture = background_images[2];
         
    }
    if (m_name == "PLAYING") {
        if (graphics::getKeyState(graphics::SCANCODE_M)) {
            m_state->get_current_level()->pause_game();
        }

    }
}

void ScreenLevel::init()
{   /*initializes all the images and brush*/
    m_back_brush.fill_opacity = 1.0f;
    m_back_brush.outline_opacity = 0.0f;
    std::string s1 = m_state->getFullAssetPath("STARTSCREEN.png"); background_images.push_back(s1);
    s1 = m_state->getFullAssetPath("RETRY.png"); background_images.push_back(s1);
    s1 = m_state->getFullAssetPath("ENDSCREEN.png"); background_images.push_back(s1);
    s1 = m_state->getFullAssetPath("helpscreen.png"); background_images.push_back(s1);
   
    m_back_brush.texture = background_images[0];
   
}

void ScreenLevel::draw()
{
   /*Draws according  to the game mode,if mode is PLAYING it draws nothing*/
    if (m_name != "PLAYING") {
        graphics::drawRect(m_state->getCanvasWidth() / 2.0, m_state->getCanvasHeight() / 2.0f,
            m_state->getCanvasWidth(), m_state->getCanvasHeight(), m_back_brush);
    }
    if (m_name == "START") {
        
        
        sprintf_s(info1, "PRESS P TO PLAY");
        graphics::drawText(m_state->getCanvasWidth() * 0.25f, m_state->getCanvasHeight() * 0.9f, 0.35f, info1, br);
        
        sprintf_s(info2, "PRESS H TO HELP");
        graphics::drawText(m_state->getCanvasWidth() * 0.25f, m_state->getCanvasHeight() * 0.95f, 0.35f, info2, br);
    }
    if (m_name == "RETRY") {
       
        sprintf_s(info1, "Your  final Score:%d", m_state->get_total_score());
        graphics::drawText(m_state->getCanvasWidth() * 0.3f, m_state->getCanvasHeight() * 0.8f, 0.3f, info1, br);
      
        sprintf_s(info2, "PRESS R TO RETRY");
        graphics::drawText(m_state->getCanvasWidth() * 0.3f, m_state->getCanvasHeight() * 0.9f, 0.3f, info2, br);
    }
    if (m_name == "END") {
        
        sprintf_s(info2, "CONGRATULATIONS");
        graphics::drawText(m_state->getCanvasWidth() * 0.3f, m_state->getCanvasHeight() * 0.95f, 0.3f, info2, br);
       
        sprintf_s(info1, "Your  final Score:%d", m_state->get_total_score());
        graphics::drawText(m_state->getCanvasWidth() * 0.3f, m_state->getCanvasHeight() * 0.9f, 0.3f, info1, br);
    }
}

ScreenLevel::ScreenLevel(const std::string& name) : GameObject(name)
{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
    pass = false;
    this->init();

}

void ScreenLevel::setMode(std::string mode)
{   /*changes the mode*/
    m_name = mode;
    pass = false;
   
}
