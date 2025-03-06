#pragma once

#include "../Entity.h"
#include "../Components/MovementComp.h"

class Pookie : public Entity {
    private:
        // components
        MovementComp* movement;
    public:
        Pookie();
};