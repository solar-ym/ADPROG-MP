#include "Game.h"

void Game::init(){
    if (player != nullptr)
        player = new Drillku("Player", "MIKU_walk1");

    sceneManager = new SceneManager();
   
    sceneManager->registerScene(new StartingScene("Starting Screen"));
    
    sceneManager->registerScene(new BattleScene("Battle Screen", roundNum, player));
    
    sceneManager->loadScene(sceneManager->SCREEN_starting);

    time_t nTime;
    srand((unsigned) time(&nTime));
    int n = rand();
    srand(n);
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
        bool isDying = player->getIsDying();
        // MOVEMENT
        if (!isAttacking && !isDying) {
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
        }

        // ATTACKING
        if(keyCode == sf::Keyboard::Scan::M && !isDying) {
            player->toggleIsAttacking(true);
            if (player->getHairVisibility() == false) player->setHairVisibility(true);
            player->setHairExtendBool(0, true);
            player->getAtkComp()->reorient();
        }

        //TEMPORARY
        if (keyCode == sf::Keyboard::Scan::I) {
            if (roundNum < 12) roundNum++;
            sceneManager->reloadBattle(roundNum);
        }
    } else if (sceneManager->getCurrentScene() == sceneManager->SCREEN_starting) { //It is at the starting screen
        if (keyCode == sf::Keyboard::Scan::M){ 
            //Player is selecting the starting button
            if(dynamic_cast<StartingScene*>
              (sceneManager->getSpecificScene(sceneManager->SCREEN_starting))->getOnStart()){
              sceneManager->loadScene(sceneManager->SCREEN_round1);
            } else //Exit from game
                cout << "SHOULD EXIT!" << endl;
        }
        if (keyCode == sf::Keyboard::Scan::W || 
            keyCode == sf::Keyboard::Scan::A ||
            keyCode == sf::Keyboard::Scan::S ||
            keyCode == sf::Keyboard::Scan::D ){
                dynamic_cast<StartingScene*>
                (sceneManager->getSpecificScene(sceneManager->SCREEN_starting))->toggleOnStart();
        }
    } else if (sceneManager->getCurrentScene() == sceneManager->SCREEN_ending) { //At the ending screen
        //If toggle is on main menu, load starting screen
        //Else close the game
    }
}

void Game::keyReleaseTrigger(Keyboard::Scan keyCode) {
    if(keyCode == sf::Keyboard::Scan::M) {
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

Game::~Game() {
    delete player;
    delete sceneManager;
}