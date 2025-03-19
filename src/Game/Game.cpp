#include "Game.h"

void Game::init(){
    // player = new Drillku("Player", "MIKU_walk1");
    // player->mikuMove(0, TILE_SIZE*8);

    // background = new Background("BG1_norm");

    // sceneManager = sceneManager->createInstance();
    cout << "Game Launched" << endl;

    sceneManager = new SceneManager();
    cout << "Scene Manager successfully created" << endl;

    sceneManager->registerScene(new StartingScene("Starting Screen"));
    cout << "Starting screen successfully created" << endl;

    sceneManager->registerScene(new BattleScene("Battle Screen", 1));
    cout << "Battle screen successfully created" << endl;

    sceneManager->loadScene(sceneManager->SCREEN_starting);

    cout << "Scene Loaded" << endl;
}

void Game::update(Time deltaTime) {
    // player->update();
    // cout << sceneManager->getCurrentScene() << endl;
    sceneManager->updateCurrentScene();
}

void Game::draw(RenderWindow *window){
    sceneManager->drawCurrentScene(window);
}

void Game::keyPressTrigger(Keyboard::Scan keyCode) {
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
    } else {
        if (keyCode == sf::Keyboard::Scan::Space) {
            cout << "Attempting to load battle..." << endl;
            sceneManager->loadScene(sceneManager->SCREEN_round1);
            cout << "   > Success." << endl;
            
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