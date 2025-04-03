#pragma once

#include "../Objects/enemies/Enemy.h"
#include "../ObjectManipulation/TunnelManager.h"

class Enemy;

class EnemyBehaviorComp : public Component {
    private:
        // int status[DIRT_HEIGHT][DIRT_WIDTH];
        TunnelManager* manager = nullptr;
        Enemy* enemy = nullptr;
        MovementComp::MOVE_TYPE prevFacing = MovementComp::RIGHT;
    public:
        EnemyBehaviorComp();
        void attachComponent(Entity* owner);

        void perform(TunnelManager* manager);
        void neutral();
        void decideFacing();
        int randomize(int lowerBound, int upperBound);
};