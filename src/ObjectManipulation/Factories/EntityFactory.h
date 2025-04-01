#pragma once

#include "../../Objects/Enemies/Enemy.h"
#include "../../Objects/Veggie.h"

class EntityFactory {
    public:
        virtual Entity* create(int id, int x, int y) = 0;
};