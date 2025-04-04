#pragma once

#include "../Objects/enemies/Enemy.h"
#include "../ObjectManipulation/TunnelManager.h"

class Enemy;

/*
    This component handles the Enemy AI.
    Further documentation provided as a .pdf in GDrive link.
*/
class EnemyBehaviorComp : public Component {
    private:
        int cooldown = 0;
        int internalTime = 70;
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

        void attack();

        void moveUp(MovementComp* move, bool tunnelExists);
        void moveDown(MovementComp* move, bool tunnelExists);
        void moveLeft(MovementComp* move, bool tunnelExists);
        void moveRight(MovementComp* move, bool tunnelExists);
};