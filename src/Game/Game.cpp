#include "Game.h"

void Game::init(){
    if (player != nullptr)
        player = new Drillku("Player", "MIKU_walk1");

    sceneManager = new SceneManager();
   
    sceneManager->registerScene(new StartingScene("Starting Screen"));
    
    sceneManager->registerScene(new BattleScene("Battle Screen", roundNum, player));
    
    sceneManager->registerScene(new EndingScreen("Win Screen"));

    sceneManager->registerScene(new EndingScreen("Lose Screen"));

    sceneManager->loadScene(sceneManager->SCREEN_starting);

    audioManager = new AudioManager();

    audioManager->loadAllMusic();
    audioManager->play(audioManager->MUSIC_START);

    time_t nTime;
    srand((unsigned) time(&nTime));
    int n = rand();
    srand(n);
}

void Game::update(Time deltaTime) {
    sceneManager->updateCurrentScene();
    if (player->getLives() <= 0) {
        player->setLives(Drillku::RESETLIVES);
        audioManager->stopAll();
        audioManager->play(audioManager->MUSIC_LOSE);
        sceneManager->loadScene(SceneManager::SCREEN_loss);
    }
}

void Game::draw(RenderWindow *window){
    sceneManager->drawCurrentScene(window);
}

void Game::keyPressTrigger(Keyboard::Scan keyCode, RenderWindow *window) {
    if (sceneManager->getCurrentScene() == sceneManager->SCREEN_battle) {
        
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

        if (keyCode == sf::Keyboard::Scan::K) {
            // if(dynamic_cast<BattleScene*>
            //   (sceneManager->getSpecificScene(sceneManager->SCREEN_battle))->getAliveEnemies() == 0){
                if (roundNum < 13) {
                    roundNum++;
                    //Plays the corresponding music based on the round number
                    //Rounds 1-4, 5-8, and 9-12 have different soundtracks
                    if(roundNum == 5){
                        audioManager->stop(audioManager->MUSIC_1to4);
                        audioManager->play(audioManager->MUSIC_5to8);
                    } else if (roundNum == 9){
                        audioManager->stop(audioManager->MUSIC_5to8);
                        audioManager->play(audioManager->MUSIC_9to12);
                    }
                }
                if (roundNum > 12) {
                    player->setLives(Drillku::RESETLIVES);
                    sceneManager->loadScene(SceneManager::SCREEN_ending);
                    audioManager->stopAll();
                    audioManager->play(audioManager->MUSIC_WIN);
                } else
                    sceneManager->reloadBattle(roundNum);
            //}
        }
        // if (keyCode == sf::Keyboard::Scan::Left) {
        //     sceneManager->loadScene(sceneManager->SCREEN_starting);
        // }
        // if (keyCode == sf::Keyboard::Scan::Right) {
        //     sceneManager->loadScene(sceneManager->SCREEN_ending);
        // }
    } else if (sceneManager->getCurrentScene() == sceneManager->SCREEN_starting) { //It is at the starting screen
        //roundNum = 1;
        if (keyCode == sf::Keyboard::Scan::M){ 
            //Player is selecting the starting button
            if(dynamic_cast<StartingScene*>
              (sceneManager->getSpecificScene(sceneManager->SCREEN_starting))->getOnStart()){
              sceneManager->loadScene(sceneManager->SCREEN_battle);
              
              audioManager->stop(audioManager->MUSIC_START);
              audioManager->play(audioManager->MUSIC_1to4);

            } else {
                sceneManager->getSpecificScene(sceneManager->SCREEN_battle)->onUnload();
                audioManager->stopAll();
                //audioManager->~AudioManager();
                window->close();
            }
        }
        if (keyCode == sf::Keyboard::Scan::W || 
            keyCode == sf::Keyboard::Scan::A ||
            keyCode == sf::Keyboard::Scan::S ||
            keyCode == sf::Keyboard::Scan::D ){
                dynamic_cast<StartingScene*>
                (sceneManager->getSpecificScene(sceneManager->SCREEN_starting))->toggleOnStart();
        }
    } else if (sceneManager->getCurrentScene() == sceneManager->SCREEN_ending || sceneManager->getCurrentScene() == sceneManager->SCREEN_loss) { //At the ending screen
        if (keyCode == sf::Keyboard::Scan::M){ 

            if(dynamic_cast<EndingScreen*>
              (sceneManager->getSpecificScene(sceneManager->getCurrentScene()))->getOnStart()){
              sceneManager->loadScene(sceneManager->SCREEN_starting);
              audioManager->stopAll();
              audioManager->play(audioManager->MUSIC_START);
            } else {
                sceneManager->getSpecificScene(sceneManager->SCREEN_battle)->onUnload();
                audioManager->stopAll();
                //audioManager->~AudioManager();
                window->close();
            }
        }
        if (keyCode == sf::Keyboard::Scan::W || 
            keyCode == sf::Keyboard::Scan::A ||
            keyCode == sf::Keyboard::Scan::S ||
            keyCode == sf::Keyboard::Scan::D ){
                dynamic_cast<EndingScreen*>
                (sceneManager->getSpecificScene(sceneManager->getCurrentScene()))->toggleOnStart();
        }
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
    delete audioManager;
}