#include "Game.h"

void Game::init(){
    cout << "Game Launched" << endl;

    if (player != nullptr) {
        player = new Drillku("Player", "MIKU_attack");
        cout << "Player created." << endl;
    }

    sceneManager = new SceneManager();
    cout << "Scene Manager successfully created" << endl;

    sceneManager->registerScene(new StartingScene("Starting Screen"));
    cout << "Starting screen successfully created" << endl;

    sceneManager->registerScene(new BattleScene("Battle Screen", 2, player));
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

        MovementComp* moveComp = player->getMoveComp();
        MovementComp::MOVE_TYPE isFacing = moveComp->isFacing();

        // MOVEMENT
        if (keyCode == sf::Keyboard::Scan::W) {
            if (isFacing == MovementComp::LEFT || isFacing == MovementComp::RIGHT)
                moveComp->reCenter(MovementComp::UP);
            moveComp->setMovementType(MovementComp::UP);
            moveComp->setMovingBool(true);

        } else if (keyCode == sf::Keyboard::Scan::S) {
            if (isFacing == MovementComp::LEFT || isFacing == MovementComp::RIGHT)
                moveComp->reCenter(MovementComp::DOWN);
            moveComp->setMovementType(MovementComp::DOWN);
            moveComp->setMovingBool(true);

        } else if (keyCode == sf::Keyboard::Scan::A) {
            if (isFacing == MovementComp::UP || isFacing == MovementComp::DOWN)
                moveComp->reCenter(MovementComp::LEFT);
            moveComp->setMovementType(MovementComp::LEFT);
            moveComp->setMovingBool(true);

        } else if (keyCode == sf::Keyboard::Scan::D) {
            if (isFacing == MovementComp::UP || isFacing == MovementComp::DOWN)
                moveComp->reCenter(MovementComp::RIGHT);
            moveComp->setMovementType(MovementComp::RIGHT);
            moveComp->setMovingBool(true);

        } 

        // ATTACKING
        if(keyCode == sf::Keyboard::Scan::Z) {
            if (player->getHairVisibility() == false) player->toggleHairVisibility();
            player->setHairExtendBool(0, true);
            player->getAtkComp()->reorient();
        }
        
        // TEMPORARY
        if (keyCode == sf::Keyboard::Scan::I) {
            player->getMoveComp()->invertTexture();
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

    if (keyCode == sf::Keyboard::Scan::W) {
        player->getMoveComp()->setMovingBool(false);
    } else if (keyCode == sf::Keyboard::Scan::S) {
        player->getMoveComp()->setMovingBool(false);
    } else if (keyCode == sf::Keyboard::Scan::A) {
        player->getMoveComp()->setMovingBool(false);
    } else if (keyCode == sf::Keyboard::Scan::D) {
        player->getMoveComp()->setMovingBool(false);
    }
}

void Game :: initializeVeggieList() {
    // push back all veggies here 
}

Game::~Game(){}