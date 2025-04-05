#pragma once

#include "../Scenes/BattleScene.h"

/*
    Handles collision in the game.
*/
class CollisionSystem{
    private: 
        int internalTime = 0;
        int cooldown = 0;
        bool running = false;

        bool enemyCollided = false;
    public:
        CollisionSystem();
        void listen(Scene* scene, vector<Enemy*> enemies, Drillku* player, TunnelManager* manager);
        
        void onPlayerCollision(int deathType, Drillku* player);

        bool collisionComputation(Entity* attacker, TunnelManager* manager);

        bool forcefulComputation(Drillku* player, Enemy* enemy, bool isPlayer);

        void update();
        
        void onAttackCollision(Scene* scene, Drillku* player, Enemy* enemy);
        void onAttackCollision(Entity* attacker);

        void fullReset();
};