#include "GameObject.h"

GameObject::GameObject() {}
GameObject::GameObject(string objName) {
    name = objName;
}
string GameObject::getName() {
    return name;
}
