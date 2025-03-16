#include "Game.h"

void Game::init(){
    // player = new Drillku("Player", "MIKU_walk1");
    // player->mikuMove(0, TILE_SIZE*8);

    // background = new Background("BG1_norm");

    // sceneManager = sceneManager->createInstance();
    cout << "Game Launched" << endl;

    sceneManager = new SceneManager();
    sceneManager->registerScene(new StartingScene("Starting Screen"));

    cout << "Scene Manager successfully created" << endl;

    sceneManager->loadScene(sceneManager->SCREEN_starting);

    cout << "Scene Loaded" << endl;
}

void Game::update(Time deltaTime) {
    // player->update();
    sceneManager->updateCurrentScene(deltaTime);
}

void Game::draw(RenderWindow *window){
    /* START OF TESTING ONLY */
    // window->draw(*background);
    // window->draw(*dirt_sprite);
    // player->draw(window);
    /* END OF TESTING ONLY */
    sceneManager->drawCurrentScene(window);
}

void Game::keyPressTrigger(Keyboard::Scan keyCode){
    if (sceneManager->getCurrentScene() != sceneManager->SCREEN_starting && 
        sceneManager->getCurrentScene() != sceneManager->SCREEN_ending) {
        // Battle Controls
        if (keyCode == sf::Keyboard::Scan::W) {
            player->getMoveComp()->move(player->getMoveComp()->UP);
        } else if (keyCode == sf::Keyboard::Scan::S) {
            player->getMoveComp()->move(player->getMoveComp()->DOWN);
        } else if (keyCode == sf::Keyboard::Scan::A) {
            player->getMoveComp()->move(player->getMoveComp()->LEFT);
        } else if (keyCode == sf::Keyboard::Scan::D) {
            player->getMoveComp()->move(player->getMoveComp()->RIGHT);
        }

        if(keyCode == sf::Keyboard::Scan::Z) {
            player->setHairExtendBool(0, true);
        }
    } 
}

void Game::keyReleaseTrigger(Keyboard::Scan keyCode) {
    if(keyCode == sf::Keyboard::Scan::Z) {
        player->setHairExtendBool(1, true);
    }
}

void Game :: initializeVeggieList() {
    // push back all veggies here 
}

Game::~Game(){}