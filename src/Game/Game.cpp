#include "Game.h"

void Game::init(){
    /* START OF TESTING ONLY */
    if(text.loadFromFile("../sprites/miku.png")){
        sprite_test = new Sprite(text);
        sprite_test->setPosition(Vector2f(0, TILE_SIZE*8));
    }

    if(bg.loadFromFile("../sprites/background.png")){
        background = new Sprite(bg);
        background->setPosition(Vector2f(0.0f, 0.0f));
    }
    /* END OF TESTING ONLY */
}

void Game::update(Time deltaTime){}

void Game::draw(RenderWindow *window){
    /* START OF TESTING ONLY */
    window->draw(*background);
    window->draw(*sprite_test);
    /* END OF TESTING ONLY */
}

void Game::keyPressTrigger(Keyboard::Scan keyCode){
    /* START OF TESTING ONLY */
    if(keyCode == sf::Keyboard::Scan::W && 
    sprite_test->getPosition().y != TILE_SIZE){
        sprite_test->move(Vector2f(0, -10.0f));
    }
    else if(keyCode == sf::Keyboard::Scan::S && 
    sprite_test->getPosition().y != (DIRT_HEIGHT + 1) * TILE_SIZE){
        sprite_test->move(Vector2f(0, 10.0f));
    }
    else if(keyCode == sf::Keyboard::Scan::A &&
    sprite_test->getPosition().x != 0.0f){
        sprite_test->move(Vector2f(-10.0f, 0));
    }
    else if(keyCode == sf::Keyboard::Scan::D &&
    sprite_test->getPosition().x != (DIRT_WIDTH - 1) * TILE_SIZE){
        sprite_test->move(Vector2f(10.0f, 0));
    }
    /* END OF TESTING ONLY */
}

void Game::keyReleaseTrigger(Keyboard::Scan keyCode){}

Game::~Game(){}