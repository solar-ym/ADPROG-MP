#pragma once

#include "../Objects/enemies/Enemy.h"
#include "../Objects/Tunnel.h"

class Enemy;

class EnemyBehaviorComp : public Component {
    private:
        int status[DIRT_HEIGHT][DIRT_WIDTH];
        Enemy* enemy = nullptr;
    public:
        EnemyBehaviorComp();
        void attachComponent(Entity* owner);

        void perform(int status[][DIRT_WIDTH]);
        void neutral();
        void decideFacing();
        int randomize(int lowerBound, int upperBound);
};