#pragma once

#include "EntityFactory.h"

class VeggieFactory : public EntityFactory {
    public:
        enum VegType {CARROT, EGGPLANT, GARLIC, LEEK,
                      MUSHROOM, PEPPER, TOMATO, TURNIP};

        Entity* create(int id);
};