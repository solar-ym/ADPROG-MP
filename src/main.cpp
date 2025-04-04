/*  
    +-------------------------------------------------------+
    |     "DIG, DRILLKU!" - GDADPRG S22 Machine Project     |
    +-------------------------------------------------------+     

                   Created and Programmed by:
                 Yza Montuerto and Megan Sadio
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
// #include "ObjectManipulation/EnemyPools.cpp"
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

/* Utilities Folder */
#include "Utility/configurations.h"
#include "Utility/SpriteManip.cpp"

int main()
{
    // Music music("../../sounds/MUSIC/MUSIC_start.mp3");
    // music.setVolume(50);
    // music.setLooping(true);
    // music.play();

    // Create a game class with the corresponding window size
    Game game;
    // Run the game
    game.run("DIG, DRILLKU!  |  GDADPRG S22 Machine Project by Sadio & Montuerto", 
            (DIRT_WIDTH + MENU_WIDTH) * TILE_SIZE,
            (DIRT_HEIGHT + SKY_HEIGHT) * TILE_SIZE);

    return 0;
}
