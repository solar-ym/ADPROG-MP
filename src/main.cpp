/*  
    +-------------------------------------------------------+
    |     "DIG, DRILLKU!" - GDADPRG S22 Machine Project     |
    +-------------------------------------------------------+     

                   Created and Programmed by:
                  Yza Montuerto and Megan Sadio

                    All Art and UI Assets by:
                  Yza Montuerto and Megan Sadio

        |------------------------------------------------|

                SOURCE CODE GITHUB REPOSITORY LINK:

               https://github.com/solar-ym/ADPROG-MP

        |------------------------------------------------|
                    BACKGROUND MUSIC CREDITS:
        - Start:
        https://www.youtube.com/watch?v=KG-Q2v2kdsw

        - Rounds 1-4:
        https://www.youtube.com/watch?v=ABQvefYR9ec

        - Rounds 5-8:
        https://www.youtube.com/watch?v=9GcYTkRoA9A

        - Rounds 9-12:
        https://www.youtube.com/watch?v=VxjledMkwyk

        - Win:
        https://www.youtube.com/watch?v=19y8YTbvri8

        - Lose:
        https://www.youtube.com/watch?v=0yNk8I-Yno4
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/* Objects Folder */
#include "Objects/GameObject.cpp"
#include "Objects/enemies/Enemy.cpp"
#include "Objects/Background.cpp"
#include "Objects/Drillku.cpp"
#include "Objects/Entity.cpp"
#include "Objects/EntityAttack.cpp"
#include "Objects/Flower.cpp"
#include "Objects/Rock.cpp"
#include "Objects/Tunnel.cpp"
#include "Objects/UIAsset.cpp"
#include "Objects/Veggie.cpp"

/* Components */
#include "Components/Component.cpp"
#include "Components/AttackComp.cpp"
#include "Components/MovementComp.cpp"
#include "Components/AnimationComp.cpp"
#include "Components/AnimationSequence.cpp"
#include "Components/EnemyBehaviorComp.cpp"

/* Game Folder */
#include "Game/BaseEngine.cpp"
#include "Game/Game.cpp"
#include "Game/CollisionSystem.cpp"
#include "Game/GD_AtlasParserM.cpp"
#include "Game/GD_GameResource.cpp"
#include "Game/RoundDataLoader.cpp"

/* Object Manipulation */
#include "ObjectManipulation/TunnelManager.cpp"
    // Factories Folder in Object Manipulation
#include "ObjectManipulation/Factories/EnemyFactory.cpp"
#include "ObjectManipulation/Factories/VeggieFactory.cpp" 

/* Scenes Folder */
#include "Scenes/Scene.cpp"
#include "Scenes/BattleScene.cpp"
#include "Scenes/SceneManager.cpp"
#include "Scenes/StartingScene.cpp"
#include "Scenes/EndingScene.cpp"

/* Sounds Folder */
#include "Sounds/AudioManager.cpp"

/* Utilities Folder */
#include "Utility/configurations.h"
#include "Utility/SpriteManip.cpp"

int main()
{
    //Create a game class with the corresponding window size
    Game game;
    // Run the game
    game.run("DIG, DRILLKU!  |  GDADPRG S22 Machine Project by Sadio & Montuerto", 
            (DIRT_WIDTH + MENU_WIDTH) * TILE_SIZE,
            (DIRT_HEIGHT + SKY_HEIGHT) * TILE_SIZE);

    return 0;
}
