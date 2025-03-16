#pragma once

#include "../Utility/configurations.h"
#include "../Objects/Entity.h"

class Component {
    protected:
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

        Entity* getOwner() {
            return owner;
        }
        string getName() {
            return compName;
        }

        // virtual void perform(sf::Time deltaTime) = 0;
};