/*  
    +------------------------------------------------------+
    |     "DIG DRILLKU!" - GDADPRG S22 Machine Project     |
    +------------------------------------------------------+     

                   Created and Programmed by:
                 Yza Montuerto and Megan Sadio
*/

#include <iostream>
#include <SFML/Graphics.hpp>

/* Objects Folder */
#include "Objects/enemies/Enemy.cpp"
#include "Objects/Drillku.cpp"

/* Components */
#include "Components/AttackComp.cpp"
#include "Components/MovementComp.cpp"
#include "Components/AnimationComp.cpp"
#include "Components/ColliderComp.cpp"
#include "Components/EnemyBehaviorComp.cpp"

/* Game Folder */
#include "Game/Game.cpp"
#include "Game/BaseEngine.cpp"
#include "Game/GD_AtlasParserM.cpp"
#include "Game/GD_GameResource.cpp"
#include "Game/RoundDataLoader.cpp"

/* Object Manipulation */
// #include "ObjectManipulation/EnemyPools.cpp"
#include "ObjectManipulation/TunnelManager.cpp"

/* Scenes Folder */
#include "Scenes/BattleScene.cpp"
#include "Scenes/SceneManager.cpp"

/* Utilities Folder */
#include "Utility/configurations.h"
#include "Utility/SpriteManip.cpp"

int main()
{
    // Create a game class with the corresponding window size
    Game game;
    // Run the game
    game.run("DRILLKU", 
            (DIRT_WIDTH + MENU_WIDTH) * TILE_SIZE,
            (DIRT_HEIGHT + SKY_HEIGHT) * TILE_SIZE);

    return 0;
}
