#pragma once

#include "EntityFactory.h"

class EnemyFactory : public EntityFactory {
    public:
        enum ENEMY_TYPE {POOKIE, GEYGAR};
        Entity* create(int id, int x, int y);
};