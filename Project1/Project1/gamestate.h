#pragma once
#include <string>
#include "sgg/graphics.h"
#include <list>
#include "Level.h"


class GameState {

private:
    std::string m_asset_path = "Assets\\";  /*Asset path*/
    float m_canvas_width = 6.0f;    /*Canvas*/
    float m_canvas_height = 6.0f;
    int total_score=0;

    bool playing = false;
    bool in_menu = true;

    static GameState* m_unique_instance;
    GameState();
    ~GameState();


    class Player* m_player = nullptr;
    class Level* m_current_level = nullptr;
    class ScreenLevel* m_current_screenlevel = nullptr;
public:
    
    bool m_debugging = false;   /*Debugging*/
    void init();
    void draw();
    void update(float dt);

    std::string getAssetDir();
    std::string getFullAssetPath(const std::string& asset);
    static GameState* getInstance();

    Level* get_current_level() { return m_current_level; }
    float getCanvasWidth() { return m_canvas_width; }
    float getCanvasHeight() { return m_canvas_height; }
    int& get_total_score() { return total_score; }
    
    void begin_playing();

    class Player* getPlayer() { return m_player; }

    void In_menu(float dt);
    void player_playing(float dt);
};