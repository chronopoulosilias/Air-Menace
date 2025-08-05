#include "Protect_ally_level.h"
#include "gamestate.h"
#include "Carrier.h"

Protect_ally_level::Protect_ally_level(int level_index) : Level(level_index)
{
    level_spawn_time = graphics::getGlobalTime();


}


void Protect_ally_level::init()
{
    Level::init();
    Carrier* ally_carrier = new Carrier();
    m_allies_to_protect.push_back(ally_carrier);

}

void Protect_ally_level::draw()
{
    Level::draw();
    for (auto gob : m_allies_to_protect) {
        gob->draw();
    }

}



void Protect_ally_level::checkcolitions(float dt) {

    Level::checkcolitions(dt);
    for (auto gob : enemies_fire) {

        for (auto ally : m_allies_to_protect) {
            if (gob->intersect(*ally)) {
                ally->lose_health();
                gob->setActive(false);
            }
        }
    }

}




void Protect_ally_level::check_defeat_condition() {

    /*Check if the players life is 0 then we set level_failed true and get a time_of_fail now*/
    if (m_state->getPlayer()->get_health() <= 0) {
        level_failed = true;
        if (time_of_fail == NULL) {
            time_of_fail = graphics::getGlobalTime();
        }
    }
    if (m_allies_to_protect.empty()) {
        level_failed = true;
        if (time_of_fail == NULL) {
            time_of_fail = graphics::getGlobalTime();
        }


    }
}

Protect_ally_level::~Protect_ally_level()
{

    Level::~Level();
    for (auto gob : m_allies_to_protect) {
        delete gob;
    }


}


void Protect_ally_level::update(float dt) {

    Level::update(dt);


}

void Protect_ally_level::remove_all_unactive_objects() {

    Level::remove_all_unactive_objects();
    remove_unactive_objects(m_allies_to_protect);




}

void Protect_ally_level::update_gameobjects(float dt)
{

    Level::update_gameobjects(dt);
    for (auto gob : m_allies_to_protect) {
        gob->update(dt);


    }
}


