#include "Colition_Manager.h"
#include "gamestate.h"


void Colition_Manager::player_fire_hits_enemy()
{
    /*For every players fire check if it has collided with any enemy,and if yes set the players fire unactive the enemy loses health*/
    for (auto gob : GameState::getInstance()->get_current_level()->m_enemies) {
        for (auto fir : GameState::getInstance()->get_current_level()->players_fire) {
            if (gob->intersect(*fir)) {
                fir->setActive(false);
                gob->lose_health();
                
                
            }
        }
    }
}

void Colition_Manager::enemy_collided_player()
{
    /*For every enemy check if he has collided with the player,and if yes set the player has collided with another plane and the enemy also loes health*/
    for (auto gob : GameState::getInstance()->get_current_level()->m_enemies) {
        if (gob->intersect(*GameState::getInstance()->getPlayer())) {
            gob->lose_health();
            GameState::getInstance()->getPlayer()->player_collided_enemy();

        }
    }
}

void Colition_Manager::enemy_fire_hits_player()
{
    for (auto gob : GameState::getInstance()->get_current_level()->enemies_fire) {
        if (gob->intersect(*GameState::getInstance()->getPlayer())) {
            GameState::getInstance()->getPlayer()->lose_health();
            gob->setActive(false);

        }
    }
}

void Colition_Manager::enemy_fire_hits_ally()
{
    for (auto gob : GameState::getInstance()->get_current_level()->enemies_fire) {
        for (auto ally : GameState::getInstance()->get_current_level()->m_allies) {
            if (gob->intersect(*ally)) {
                ally->lose_health();
                gob->setActive(false);
            }
        }

     }
}

void Colition_Manager::player_got_powerup()
{
    for (auto gob : GameState::getInstance()->get_current_level()->powerups) {
        if (gob->intersect(*GameState::getInstance()->getPlayer())) {
            if (gob->getpick() == 0) {
                GameState::getInstance()->getPlayer()->get_shield();
            }
            else if (gob->getpick() == 1) {
                GameState::getInstance()->getPlayer()->get_health_boost();
            }
            else if (gob->getpick() == 2) {
                GameState::getInstance()->getPlayer()->get_faster_reload();
            }
            else {
                GameState::getInstance()->get_current_level()->spawn_allies();
            }
            gob->setActive(false);


        }

    }
}

void Colition_Manager::check_colitions()
{
    player_fire_hits_enemy();
    enemy_collided_player();
    enemy_fire_hits_player();
    enemy_fire_hits_ally();
    player_got_powerup();
}
