#include "Game.h"

void Game::init(){
    cout << "Game Launched" << endl;

    if (player != nullptr) {
        player = new Drillku("Player", "MIKU_walk1");
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
        
        bool isAttacking = player->getAtkComp()->isVisible();
        // MOVEMENT
        if (keyCode == sf::Keyboard::Scan::W && !isAttacking) {
            if (isFacing == MovementComp::LEFT || isFacing == MovementComp::RIGHT)
                moveComp->reCenter(MovementComp::UP);
            moveComp->setMovementType(MovementComp::UP);
            moveComp->setMovingBool(true);
        } else if (keyCode == sf::Keyboard::Scan::S && !isAttacking) {
            if (isFacing == MovementComp::LEFT || isFacing == MovementComp::RIGHT)
                moveComp->reCenter(MovementComp::DOWN);
            moveComp->setMovementType(MovementComp::DOWN);
            moveComp->setMovingBool(true);

        } else if (keyCode == sf::Keyboard::Scan::A && !isAttacking) {
            if (isFacing == MovementComp::UP || isFacing == MovementComp::DOWN)
                moveComp->reCenter(MovementComp::LEFT);
            moveComp->setMovementType(MovementComp::LEFT);
            moveComp->setMovingBool(true);

        } else if (keyCode == sf::Keyboard::Scan::D && !isAttacking) {
            if (isFacing == MovementComp::UP || isFacing == MovementComp::DOWN)
                moveComp->reCenter(MovementComp::RIGHT);
            moveComp->setMovementType(MovementComp::RIGHT);
            moveComp->setMovingBool(true);
        } 

        // ATTACKING
        if(keyCode == sf::Keyboard::Scan::Z) {
            player->toggleIsAttacking(true);
            if (player->getHairVisibility() == false) player->toggleHairVisibility();
            player->setHairExtendBool(0, true);
            player->getAtkComp()->reorient();
        }

        if (keyCode == sf::Keyboard::Scan::Space) {
            cout << "Attempting to load start..." << endl;
            sceneManager->loadScene(sceneManager->SCREEN_starting);
            cout << "   > Success." << endl;
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
        player->toggleIsAttacking(false);
        player->setHairExtendBool(1, true);
    }

    MovementComp* moveComp = player->getMoveComp();
    MovementComp::MOVE_TYPE isFacing = moveComp->isFacing();

    if (keyCode == sf::Keyboard::Scan::W && isFacing == MovementComp::UP) {
        player->getMoveComp()->setMovingBool(false);
    } else if (keyCode == sf::Keyboard::Scan::S && isFacing == MovementComp::DOWN) {
        player->getMoveComp()->setMovingBool(false);
    } else if (keyCode == sf::Keyboard::Scan::A && isFacing == MovementComp::LEFT) {
        player->getMoveComp()->setMovingBool(false);
    } else if (keyCode == sf::Keyboard::Scan::D && isFacing == MovementComp::RIGHT) {
        player->getMoveComp()->setMovingBool(false);
    }
}

void Game :: initializeVeggieList() {
    // push back all veggies here 
}

Game::~Game() {
    delete player;
    delete sceneManager;
}