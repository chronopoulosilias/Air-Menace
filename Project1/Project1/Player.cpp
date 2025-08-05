#include "Player.h"
#include <sgg/graphics.h>
#include "gamestate.h"
#include "util.h"
#include "Fire.h"
#include "Level.h"
#include "Laser.h"
#include "ally_fighter.h"


Player::Player(const std::string& name) : GameObject(name)
{
    m_height = 0.4f;
    m_width = 0.4f;
}

void Player::update(float dt)
{   /*Move the player according to the buttons,hold him inside the canvas,and fire*/
    float delta_time = dt / 1000.0f;
    
    if (graphics::getKeyState(graphics::SCANCODE_W)) {
        m_pos_y -= player_velocity * delta_time;
    }
    if (graphics::getKeyState(graphics::SCANCODE_S)) {
        m_pos_y += player_velocity * delta_time;
    }
    if (graphics::getKeyState(graphics::SCANCODE_A)) {
        m_pos_x -= player_velocity * delta_time;
    }
    if (graphics::getKeyState(graphics::SCANCODE_D)) {
        m_pos_x += player_velocity * delta_time;
    }
    hold_in_canvas();
    check_faster_reload();
    check_shield();
    change_weapon();

    player_fire();
    plane_crashed();
}

void Player::init()
{   /*sets the initial potision of player*/
    m_pos_x = m_state->getCanvasWidth() * 0.5f;
    m_pos_y = m_state->getCanvasHeight() * 0.9f;
    

    /*init*/
    m_brush_player.fill_opacity = 1.0f;
    m_brush_player.outline_opacity = 0.0f;
    m_brush_player.texture = m_state->getFullAssetPath("player.png"); 
    m_brush_player_debugging.fill_opacity = 0.1f;
    m_brush_player_debugging.outline_opacity = 1.0f;
    SETCOLOR(m_brush_player_debugging.fill_color, 0.1f, 1.0f, 0.1f;)


}

void Player::draw()
{   
    /*Draw*/
    graphics::drawRect(m_pos_x, m_pos_y,
        m_height , m_width, m_brush_player);
    /*Debugging Draw*/
    if (m_state->m_debugging) {
        graphics::drawRect(m_pos_x, m_pos_y,
            m_height , m_width , m_brush_player_debugging);
    }
    
}

void Player::hold_in_canvas()
{
    /*Holds the player inside the canvas*/
    if (m_pos_x < m_state->getCanvasWidth()*0.025f) {
        m_pos_x = m_state->getCanvasWidth() * 0.025f;
        
    }
    if (m_pos_x > m_state->getCanvasWidth() * 0.975f) {
        m_pos_x = m_state->getCanvasWidth() * 0.975f;

    }
    if (m_pos_y > m_state->getCanvasHeight() * 0.975f) {
        m_pos_y = m_state->getCanvasWidth() * 0.975f;

    }
    if (m_pos_y < m_state->getCanvasHeight() * 0.045f) {
        m_pos_y = m_state->getCanvasWidth() * 0.045f;

    }
   

}

void Player::plane_crashed()
{   /*If HP=0 then the player is unactive*/
    if (health_points <= 0) {
        this->setActive(false);
        explotion* ex = new explotion(m_pos_x, m_pos_y, m_width, m_height);
        m_state->get_current_level()->explotions.push_back(ex);
    }
}


void Player::ressurect()
{
    m_pos_x = m_state->getCanvasWidth() * 0.5f;
    m_pos_y = m_state->getCanvasHeight() * 0.9f;
    this->setActive(true);
    regain_max_health();
    lose_powerups();
}

/*POWERUPS*/
void Player::get_shield()
{
    shielded = true;
    time_of_shield = graphics::getGlobalTime();
}

void Player::check_shield()
{
    if (((graphics::getGlobalTime() - time_of_shield) > shield_duration) && shielded) {
        shielded = false;
    }
}

void Player::get_faster_reload()
{
    faster_reload = true;
    main_weapon_time_reloading = 250.0f;
    timeof_faster_reload = graphics::getGlobalTime();
}

void Player::lose_powerups()
{
    faster_reload = false;
    shielded = false;
    secondary_weapon_loaded = 500.0f;

}

void Player::get_health_boost()
{
    health_points += 3;
    if (health_points > 10) { health_points = 10; }
}


void Player::check_faster_reload()
{
    if (((graphics::getGlobalTime() - timeof_faster_reload) > faster_reload_duration) && faster_reload) {
        faster_reload = false;
        secondary_weapon_loaded = 500.0f;
    }

}

void Player::get_allies()
{


}

/*END_POWERUPS*/


/*FIRING AND WEAPONS*/
void Player::change_weapon()
{
    if (graphics::getKeyState(graphics::SCANCODE_V) && (graphics::getGlobalTime() - time_change_weapons > time_to_change_weapon)) {
        if (main_weapon_equiped) {
            main_weapon_equiped = false;
            secondary_weapon_equiped = true;
        }
        else {
            main_weapon_equiped = true;
            secondary_weapon_equiped = false;
        }
        time_change_weapons = graphics::getGlobalTime();
    }
}



void Player::player_fire()
{
    if (main_weapon_equiped) {
        /*Fire method: if the gun is loaded and the player presses P,create a new fire and give it to the current level, set the gun_loaded=false and get the time of shot*/
        if (main_weapon_loaded && graphics::getKeyState(graphics::SCANCODE_P)) {
            Projectile* fire = new Fire(m_state->getPlayer()->m_pos_x, m_state->getPlayer()->m_pos_y, 3 * 3.14f / 2, 3.0f);
            m_state->get_current_level()->players_fire.push_back(fire);
            main_weapon_loaded = false;
            time_of_shot = graphics::getGlobalTime();
            graphics::playSound(m_state->getFullAssetPath("shoot.mp3"), 0.1f);
        }
        /*If the gun is not loaded check if the time passed(player_time_reloading) since the last time_of_shot*/
        if (graphics::getGlobalTime() - time_of_shot > main_weapon_time_reloading) {
            main_weapon_loaded = true;
        }
    }
    else if(secondary_weapon_equiped){
        if (secondary_weapon_loaded && graphics::getKeyState(graphics::SCANCODE_P)) {
            Projectile* laser = new Laser(m_state->getPlayer()->m_pos_x, m_state->getPlayer()->m_pos_y, 3 * 3.14f / 2, 3.0f);
            m_state->get_current_level()->players_fire.push_back(laser);
            secondary_weapon_loaded = false;
            time_of_shot = graphics::getGlobalTime();
            graphics::playSound(m_state->getFullAssetPath("shoot.mp3"), 0.1f);
        }
        /*If the gun is not loaded check if the time passed(player_time_reloading) since the last time_of_shot*/
        if (graphics::getGlobalTime() - time_of_shot > secondary_weapon_time_reloading) {
            secondary_weapon_loaded = true;
        }
    
    
    
    
    }
}
    
/*END_FIRING AND WEAPONS*/
 


