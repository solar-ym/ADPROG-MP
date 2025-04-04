#pragma once

#include "EntityFactory.h"

class VeggieFactory : public EntityFactory {
    public:
        enum VegType {CARROT, TURNIP, MUSHROOM, LEEK,
                      EGGPLANT, PEPPER, TOMATO, GARLIC};

        Entity* create(int id, int x, int y);
};