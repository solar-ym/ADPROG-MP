#pragma once

#include "../Objects/Entity.h"
#include "../Objects/Enemies/Enemy.h"

class EntityFactory {
    public:
        virtual Entity* create(int id) = 0;
};

class EnemyFactory : public EntityFactory {
    public:
        enum enemyType {POOKIE, GEYGAR};
        Entity* create(enemyType id) {
            Enemy* newEnemy;
            switch (id) {
                case POOKIE: 
                    // newEnemy = new Enemy("Pookie", "")
                    break;
                case GEYGAR: 
                    // newEnemy = new Enemy("Pookie", "")
                    break;
                default: break;
            }
            return newEnemy;
        }
};

class FruitFactory : public EntityFactory {
    public:
        Entity* create(int id) {

        }
};

class FlowerFactory : public EntityFactory {
    public:
        Entity* create(int id) {

        }
};