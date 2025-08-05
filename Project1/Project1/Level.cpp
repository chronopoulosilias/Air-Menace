#include "Level.h"
#include "gamestate.h"
#include "Player.h"
#include "Fire.h"
#include "Enemy.h"
#include "Bomber.h"
#include "Kamikazi.h"
#include "Battleship.h"
#include "util.h"
#include <fstream>
#include <iostream>
#include "explosion.h"
#include "ally_fighter.h"
#include "Enemy_Spawner.h"
#include "UI.h"
#include "Colition_Manager.h"

Level::Level(int level_index) : level_index(level_index)
{
    level_spawn_time = graphics::getGlobalTime();
     level_ui = new UI();

}

void Level::update(float dt)
{
    if (game_paused != true) {
        /*Update player,enemies,fires,and explotions*/
        update_gameobjects(dt);

        Colition_Manager().check_colitions();/*Checks the colitions*/

        remove_all_unactive_objects();
        
        /*Removes every unactive object to save memory*/
        
        check_defeat_condition();
        chech_win_condition();
        //UI().update(dt);
       



        GameObject::update(dt);
    }
    else {
        level_spawn_time += dt;
    }
}

void Level::init()
    {
    Enemy_Spawner().fill_level_enemies(level_index);
   /*Initialize the brushes*/
    level_ui->init();
    m_back_brush.fill_opacity = 1.0f;
    m_back_brush.outline_opacity = 0.0f;
    m_back_brush.texture = m_state->getFullAssetPath("seaback.png");

    
    
    /*Initializes the enemies of the level*/

    for (auto gob : m_enemies) {
        gob->init();
    }
    
    
}

void Level::draw()
{   
    
   
    /*background*/
    graphics::drawRect(m_state->getCanvasWidth() / 2.0f , m_state->getCanvasHeight() / 2.0f ,
        m_state->getCanvasWidth() * 2.0f, m_state->getCanvasHeight() * 4.0f, m_back_brush);
   
    level_ui->draw();



    /*Draw player,enemies,fires,and explotions*/
    if (m_state->getPlayer()->isActive()) {
        m_state->getPlayer()->draw();
    }
    for (auto gob : explotions) {
        gob->draw();
    }
    for (auto gob : m_enemies) {
        gob->draw();
    }
    for (auto gob : players_fire) {
        gob->draw();
    }
    for (auto gob : enemies_fire) {
        gob->draw();
    }
    for (auto gob : powerups) {
        gob->draw();
    }
    for (auto gob : m_allies) {
        gob->draw();
    }
   
    
    
    

    
}






void Level::spawn_allies()
{
    ally_fighter* ally1 = new ally_fighter(true);
    ally_fighter* ally2 = new ally_fighter(false);
    m_allies.push_back(ally1);
    m_allies.push_back(ally2);
}

void Level::checkcolitions(float dt)
{
    
    /*For every enemy check if he has collided with the player,and if yes set the player has collided with another plane and the enemy also loes health*/
    for (auto gob : m_enemies) {
        if (gob->intersect(*m_state->getPlayer())) {
            gob->lose_health();
            m_state->getPlayer()->player_collided_enemy();
            
        }
    }
    /*For every enemies fire check if it has collided with the player,and if yes set the enemies fire unactive and the player loses health*/
    for (auto gob : enemies_fire) {
        if (gob->intersect(*m_state->getPlayer())) {
            m_state->getPlayer()->lose_health();
            gob->setActive(false);

        }

        for (auto ally : m_allies) {
            if (gob->intersect(*ally)) {
                ally->lose_health();
                gob->setActive(false);
            }
        }
    }

   
    
}








Level::~Level()
{   /*Delete enemies,fires,and explotions*/
    for (auto gob : explotions) {
        delete gob;
    }
    for (auto gob : players_fire) {
        delete gob;
    }
    for (auto gob : m_enemies) {
        delete gob;
    }
    for (auto gob : enemies_fire) {
        delete gob;
    }
    for (auto gob : powerups) {
        delete gob;
    }
    for (auto gob : m_allies) {
        delete gob;
    }

    delete level_ui;
  
    
}

void Level::pause_game()
{   /*pause-unpause game*/
    if (game_paused) { game_paused = false; }
    else { game_paused = true; }
}

void Level::remove_all_unactive_objects()
{
    remove_unactive_objects(players_fire);
    remove_unactive_objects(enemies_fire);
    remove_unactive_objects(m_enemies);
    remove_unactive_objects(explotions);
    remove_unactive_objects(powerups);
    remove_unactive_objects(m_allies);
}


void Level::chech_win_condition()
{
    /*Check if all enemies are unactive then we set level_passed true and get a time_of_pass now*/
    if (m_enemies.empty()) {
        level_passed = true;
        if (time_of_pass == NULL) {
            time_of_pass = graphics::getGlobalTime();
        }
    }
   
}
void Level::check_defeat_condition()
{
    /*Check if the players life is 0 then we set level_failed true and get a time_of_fail now*/
    if (m_state->getPlayer()->get_health() <= 0) {
        level_failed = true;
        if (time_of_fail == NULL) {
            time_of_fail = graphics::getGlobalTime();
        }
    }
}

void Level::update_gameobjects(float dt)
{
    if (m_state->getPlayer()->isActive()) {
        m_state->getPlayer()->update(dt);
    }
    for (auto gob : explotions) {
        gob->update(dt);
    }
    for (auto gob : m_enemies) {
        gob->update(dt);
    }
    for (auto gob : players_fire) {
        gob->update(dt);
    }
    for (auto gob : enemies_fire) {
        gob->update(dt);
    }
    for (auto gob : powerups) {
        gob->update(dt);
    }
    for (auto gob : m_allies) {
        gob->update(dt);


    }
}



/*If the level_passed == true and the time that has passed since the condition was met is bigger than the time_of_pause,the level has passed*/
bool Level::level_has_passed()
{
    if (level_passed == true && graphics::getGlobalTime() - time_of_pass > time_of_pause) {
        return true;
    }
    else {
        return false;
    }
}

/*If the level_failed == true and the time that has passed since the condition was met is bigger than the time_of_pause,the level has failed*/
bool Level::level_has_failed()
{
    if (level_failed == true && graphics::getGlobalTime() - time_of_fail > time_of_pause) {
        return true;
    }
    else {
        return false;
    }
}

