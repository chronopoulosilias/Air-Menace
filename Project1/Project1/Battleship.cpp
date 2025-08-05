#include "Battleship.h"
#include "GameObject.h"
#include "gamestate.h"
#include "util.h"
#include "Fire.h"
#include "Level.h"
#include "cmath"
#include "Gun.h"

Battleship::Battleship(const std::string& name, const float& potision,  float generation_time) : Enemy(name, potision, generation_time)
{   /*initializes variables from parent Enemy and Box(m_height,m_width)*/
    health_points = 20;
    m_height = 1.15f;
    m_width = 0.25f;
    enemy_velocity = 0.3f;
    points = 100;
    enemy_time_reloading = 2000.0f;
    fire_velocity = 2.0f;

    /*Creates the 2 guns of the battleship which it will initalize,draw and also update and also sets time to reload and fire_velocity of each one for bigger game difficulty*/
    gun1 = new Gun("gun1", potision, generation_time, this); gun1->set_fire_velocity(2.0f); gun1->set_enemy_time_reloading(2000.0f);
    gun2 = new Gun("gun2", potision, generation_time, this); gun1->set_fire_velocity(4.0f); gun1->set_enemy_time_reloading(4000.0f);
}

Battleship::~Battleship()
{   /*The guns must also get deleted with the battleship*/
    if (gun1) {
        delete gun1;
    }
    if (gun2) {
        delete gun2;
    }
}

void Battleship::update(float dt)
{
    /*We get the time now in the level(each level has its own time),and if time now is bigger than the generation_time,the battleship
    starts moving in the y axis until position_set=true(then starts moving left and right in the x axis),fires and lastly we check if it has crashed and update its guns also*/
    float time = graphics::getGlobalTime() / 1000.0f - m_state->get_current_level()->get_level_spawn_time() / 1000.0f;
    if (time > generation_time) {
        float delta_time = dt / 1000.0f;
        if (m_pos_y < m_state->getCanvasHeight() * 0.35f) {
            m_pos_y += enemy_velocity * delta_time;
        }
        else { position_set = true; }
        if (position_set) {
            if (m_pos_x < m_state->getCanvasHeight() * 0.35f) {
                x_direction = 1.0f;
            }
            else if (m_pos_x > m_state->getCanvasHeight() * 0.85f) {
                x_direction = -1.0f;
            }
            m_pos_x += x_direction * enemy_velocity * delta_time;

        }
        enemy_fire();
        plane_crashed();

        if (gun1) {
            gun1->update(dt);
        }
        if (gun2) {
            gun2->update(dt);
        }

        
    }
   
}


void Battleship::init()
{
    
    Enemy::init();
    m_brush_enemy.texture = m_state->getFullAssetPath("Destroyer.png");
    if (gun1) {
        gun1->init();
    }
    if (gun2) {
        gun2->init();
    }
    
}

void Battleship::draw()
{
    Enemy::draw();
    if (gun1) {
        gun1->draw();
    }
    if (gun2) {
        gun2->draw();
    }
    
}

void Battleship::enemy_fire()
{
    
    /*if the gun is loaded it creates many fires to every direction with the variable angle,and gives it to the current level */
    if (gun_loaded(enemy_time_reloading)) {
        float angle = 0.0f;
        while (angle < 2 * 3.14f) {
            Fire* fire = new Fire(m_pos_x, m_pos_y, angle, fire_velocity);
            m_state->get_current_level()->enemies_fire.push_back(fire);
            angle += 3.14f / 4;
        }
    }
}

void Battleship::plane_crashed()
{
    /*if health points gets zero we add the enemy points to the total score of the game,
    then make the enemy unactive so it will get deleted and create 3 exlpotions that we pass on the current level*/
    if (health_points == 0) {
        m_state->get_total_score() += points;
        this->m_active = false;
        explotion* ex1 = new explotion(m_pos_x, m_pos_y, m_width*1.2f, m_width * 1.2f);
        explotion* ex2 = new explotion(m_pos_x, m_pos_y-0.35f, m_width * 1.2f, m_width * 1.2f);
        explotion* ex3 = new explotion(m_pos_x, m_pos_y+0.35f, m_width * 1.2f, m_width * 1.2f);
        m_state->get_current_level()->explotions.push_back(ex1);
        m_state->get_current_level()->explotions.push_back(ex2);
        m_state->get_current_level()->explotions.push_back(ex3);
    }
}


