#pragma once

#include "Component.h"

class MovementComp : public Component {
    private:
        enum MOVE_TYPE {UP, DOWN, LEFT, RIGHT};
    public:
        MovementComp(string name);

};