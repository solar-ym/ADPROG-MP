#include "Game.h"

void Game::init(){
    /* START OF TESTING ONLY */

    player = new Drillku("Player");
    player->mikuMove(0, TILE_SIZE*8);

    if(bg.loadFromFile("../../sprites/background.png")){
        background = new Sprite(bg);
        background->setPosition(Vector2f(0.0f, 0.0f));
    }
    /* END OF TESTING ONLY */
}

void Game::update(Time deltaTime) {
    player->update();
}

void Game::draw(RenderWindow *window){
    /* START OF TESTING ONLY */
    window->draw(*background);
    // window->draw(*dirt_sprite);
    player->draw(window);
    /* END OF TESTING ONLY */
}

void Game::keyPressTrigger(Keyboard::Scan keyCode){

    if (keyCode == sf::Keyboard::Scan::W) {
        player->getMoveComp()->move(player->getMoveComp()->UP);
    }
    else if (keyCode == sf::Keyboard::Scan::S) {
        player->getMoveComp()->move(player->getMoveComp()->DOWN);
    }
    else if (keyCode == sf::Keyboard::Scan::A) {
        player->getMoveComp()->move(player->getMoveComp()->LEFT);
    }
    else if (keyCode == sf::Keyboard::Scan::D) {
        player->getMoveComp()->move(player->getMoveComp()->RIGHT);
    }

    /* END OF TESTING ONLY */
    if(keyCode == sf::Keyboard::Scan::Z) {
        player->setHairExtendBool(0, true);
    }
}

void Game::keyReleaseTrigger(Keyboard::Scan keyCode) {
    if(keyCode == sf::Keyboard::Scan::Z) {
        player->setHairExtendBool(1, true);
    }
}

Game::~Game(){}