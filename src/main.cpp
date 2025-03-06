#include <iostream>
#include <SFML/Graphics.hpp>

/* Objects Folder */
// #include "Objects/Entity.h"
// #include "Objects/enemies/Pookie.cpp"
#include "Objects/Drillku.cpp"

/* Components */
#include "Components/AttackComp.cpp"
#include "Components/MovementComp.cpp"

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
