
#include "sgg/graphics.h"
#include <stdio.h>
#include <string>
#include "util.h"
#include "gamestate.h"
#include <iostream>


void init() {
    GameState::getInstance()->init();

}
void draw() {
    GameState::getInstance()->draw();


}
void update(float dt) {

    GameState::getInstance()->update(dt);
    std::cout << dt << std::endl;
}




int main(int argc, char** argv)
{


    graphics::createWindow(800, 800, "AIR ACE");
    init();
    
    
   
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);
    

    graphics::setCanvasSize(GameState::getInstance()->getCanvasHeight(), GameState::getInstance()->getCanvasWidth());
    
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::startMessageLoop();



    return 0;
}


