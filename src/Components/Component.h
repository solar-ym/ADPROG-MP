#pragma once

#include "../Utility/configurations.h"
#include "../Utility/SpriteManip.h"

/*
    Base class for components.
*/
class Component {
    protected:
        string compName;
        Entity* owner;
    public:
        Component();
        Component(string compName);

        void attachComponent(Entity* owner);

        Entity* getOwner();
        string getName();
};