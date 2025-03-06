#pragma once

#include "../Utility/configurations.h"
#include "../Objects/Entity.h"

class Component {
    private:
        string compName;
        Entity* owner;
    public:
        Component() {}
        Component(string compName) {
            this->compName = compName;
        }

        void attachComponent(Entity* owner) {
            this->owner = owner;
        }
};