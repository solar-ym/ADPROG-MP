#pragma once

#include "../Scenes/Scene.h"

class CollisionSystem{
    private: 
        int internalTime = 0;
        bool running = false;

        bool enemyCollided = false;
    public:
        CollisionSystem();
        void listen(Scene* scene, vector<Enemy*> enemies, Drillku* player, TunnelManager* manager);
        
        void onPlayerCollision(Scene* scene, Drillku* player, Enemy* enemy);

        bool collisionComputation(Entity* attacker, TunnelManager* manager);

        bool forcefulComputation(Drillku* player, Enemy* enemy, bool isPlayer);

        void update();
        
        void onAttackCollision(Scene* scene, Drillku* player, Enemy* enemy);
        void onAttackCollision(Entity* attacker);
};