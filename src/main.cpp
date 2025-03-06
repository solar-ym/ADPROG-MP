#include <iostream>
#include <SFML/Graphics.hpp>

/* Game Folder */
#include "Game/Game.cpp"
#include "Game/BaseEngine.cpp"

/* Utilities Folder */
#include "Utility/configurations.h"

int main()
{
    Game game;
    game.run("DRILLKU", 
            (DIRT_WIDTH + MENU_WIDTH) * TILE_SIZE,
            (DIRT_HEIGHT + SKY_HEIGHT) * TILE_SIZE);
    return 0;
    
}
