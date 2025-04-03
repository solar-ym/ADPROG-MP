#pragma once

#include "../Objects/enemies/Enemy.h"
#include "../ObjectManipulation/TunnelManager.h"

class Enemy;

class EnemyBehaviorComp : public Component {
    private:
        int internalTime = 0;
        Drillku* target = nullptr;
        TunnelManager* manager = nullptr;
        Enemy* enemy = nullptr;
        MovementComp::MOVE_TYPE prevFacing = MovementComp::RIGHT;
    public:
        EnemyBehaviorComp();
        void attachComponent(Entity* owner);
        void makeTarget(Drillku* player);
        
        void perform(TunnelManager* manager);
        void neutral();
        bool targetDetected();
        void chase();
        void ghostChase();
        void decideFacing();

        // void findTunnel();
};