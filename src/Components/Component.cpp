#include "Component.h"

Component::Component() {}
Component::Component(string compName) {
    this->compName = compName;
}

void Component::attachComponent(Entity* owner) {
    this->owner = owner;
}

Entity* Component::getOwner() {
    return owner;
}
string Component::getName() {
    return compName;
}
