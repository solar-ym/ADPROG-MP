#pragma once

#include "../Scenes/Scene.h"

class CollisionSystem{
    private: 
        int internalTime = 0;
        bool running = false;
    public:
        CollisionSystem();
        void listen(Scene* scene, vector<Enemy*> enemies, Drillku* player);
        
        void onPlayerCollision(Scene* scene, Drillku* player, Enemy* enemy);

        bool collisionComputation(ColliderComp* obj1, ColliderComp* obj2 );

        bool forcefulComputation(Drillku* player, Enemy* enemy);

        void update();
        
        void onAttackCollision(Scene* scene, Drillku* player, Enemy* enemy);
};