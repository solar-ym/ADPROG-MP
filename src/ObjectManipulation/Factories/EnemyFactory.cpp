#include "EnemyFactory.h"

// Makes enemies
Entity* EnemyFactory::create(int id, int x, int y) {
    string name, texturePath;
    if (!id) {
        name = "Pookie";
        texturePath = "POOKIE_walk1";
    } else {
        name = "Geygar";
        texturePath = "GEYGAR_walk1";
    }
    
    Enemy* newEnemy = new Enemy(name, texturePath);

    newEnemy->setTileXY(x, y);
    newEnemy->addComponent(new MovementComp("MoveComp", MovementComp::ENEMY, newEnemy->getSprite()));
    newEnemy->addComponent(new AnimationComp("AnimationComp"));
    newEnemy->addComponent(new EnemyBehaviorComp());

    newEnemy->getAnimComp()->loadFrames();

    return newEnemy;
}
