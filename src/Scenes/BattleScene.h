#pragma once

#include "Scene.h"
#include "../Game/RoundDataLoader.h"
#include "../ObjectManipulation/TunnelManager.h"
#include "../Objects/Drillku.h"
#include "../Game/CollisionSystem.h"
#include "../Objects/Background.h"
#include "../Objects/UIAsset.h"

#include "../Objects/Flower.h"
#include "../Objects/Rock.h"

class BattleScene : public Scene {
    private:
        int roundNum;
        int prevRoundNum;
        vector<int> roundData;
        Drillku* player;
        Tunnel* currentTunnel = nullptr;
        MovementComp::MOVE_TYPE lastFacing = MovementComp::RIGHT;

        CollisionSystem* colSystem;
        EnemyFactory enemyMaker;
        vector<Enemy*> currentEnemies;

        RoundDataLoader dataLoader;
        TunnelManager* tunManager;

        vector<UIAsset*> noOfLives;
        UIAsset* uiPressK;
        UIAsset* uiNextRound;
        vector<Flower*> currentFlowers;

        Vector2i playerPrevTile;

        VeggieFactory veggieMaker;
        vector<Veggie*> currentVeggies;
        Veggie* roundVeggie;

        vector<Rock*> currentRocks;
        int droppedRocks = 0;
    public:
        BattleScene(string name, int roundNum, Drillku* player);

        void onLoad();
        void onUnload();
        void reloadRoundData();

        void dig();
        void fixTunnel();
        void createTunnel(Tunnel::TunnelType stage);

        void update();
        void draw(RenderWindow* window);

        // Used to create the starting tunnels that exist to hold enemies
        void initStartTunnel();
        void initializeTunnel(int x, int y, int enemyType, int type);
        void makeRocks();
        
        int getAliveEnemies();

        void setRoundNum(int id);

        Veggie* getRoundVeggie();
        vector<Rock*> getAllRocks();
};