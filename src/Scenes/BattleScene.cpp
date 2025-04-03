#include "BattleScene.h"

BattleScene :: BattleScene(string name, int roundNum, Drillku* player) : Scene(name) {
    roundData.clear();
    this->roundNum = roundNum;
    this->player = player;

    colSystem = new CollisionSystem();
    tunManager = new TunnelManager();
    // pookiePool = new EnemyPool(4, EnemyFactory::POOKIE);
    // geygarPool = new EnemyPool(3, EnemyFactory::GEYGAR);
}

void BattleScene :: onLoad() {
    roundData = dataLoader.loadData(roundNum);

    Background* bg  = new Background("BG1_norm");
    addObject(bg);

    // TUNNELS
    for (int i = 0; i < roundData.size(); i += 4) {
        initializeTunnel(roundData[i], roundData[i+1], roundData[i+2], roundData[i+3]);
    }
}

void BattleScene :: onUnload() {
    removeAllObjects();
    if (!roundData.empty()) {
        roundData.clear();
    }

    tunManager->fullReset();
    lastFacing = MovementComp::RIGHT;
    currentEnemies.clear();
    delete currentTunnel;
    delete colSystem;
}

void BattleScene :: reloadRoundData() {
    getAllObjects().clear();

    if (roundNum < 5) {
        Background* bg  = new Background("BG1_norm");
        addObject(bg);
    } else if (roundNum > 8) {
        Background* bg  = new Background("BG3_norm");
        addObject(bg);
    } else {
        Background* bg  = new Background("BG2_norm");
        addObject(bg);
    }
    cout << "[BATTLE SCREEN] New background created" << endl;

    if (!roundData.empty()) {
        roundData.clear();
    }

    tunManager->fullReset();

    currentTunnel = nullptr;
    lastFacing = MovementComp::RIGHT;
    currentEnemies.clear();
    
    roundData = dataLoader.loadData(roundNum);
    
    for (int i = 0; i < roundData.size(); i += 4) {
        initializeTunnel(roundData[i], roundData[i+1], roundData[i+2], roundData[i+3]);
    }

    player->setTileXY(6,6);
}

void BattleScene :: dig() {
    if (currentTunnel == nullptr && !(tunManager->hasTunnel(player->getTileX(), player->getTileY()))) {
        createTunnel(Tunnel::STRAIGHT);
    } else if (currentTunnel != nullptr) {
        currentTunnel->extend(player->getMoveComp()->isFacing());
        player->toggleIsDigging(true);
    }

    if (currentTunnel != nullptr && currentTunnel->isMaxExtended() &&
        (player->getTileX() != currentTunnel->getTileX() ||
        player->getTileY() != currentTunnel->getTileY())) {  
            currentTunnel = nullptr;
            player->toggleIsDigging(false);
    }
}

void BattleScene :: fixTunnel() {
    currentTunnel->maxExtend();
    currentTunnel->getSprite()->setRotation(degrees(0));

    switch (player->getMoveComp()->isFacing()) {
        case MovementComp::UP:
            if (lastFacing == MovementComp::LEFT) {
                currentTunnel->changeTunnelType(Tunnel::CORNER);
            } else if (lastFacing == MovementComp::RIGHT) {
                currentTunnel->changeTunnelType(Tunnel::CORNER);
                SpriteManip::turnLeft(currentTunnel);
            } else if (lastFacing == MovementComp::DOWN) {
                currentTunnel->changeTunnelType(Tunnel::CAP);
                SpriteManip::turnLeft(currentTunnel);
                SpriteManip::turnLeft(currentTunnel);
            }
            break;
        case MovementComp::DOWN:
            if (lastFacing == MovementComp::LEFT) {
                currentTunnel->changeTunnelType(Tunnel::CORNER);
                SpriteManip::turnRight(currentTunnel);
            } else if (lastFacing == MovementComp::RIGHT) {
                currentTunnel->changeTunnelType(Tunnel::CORNER);
                SpriteManip::turnRight(currentTunnel);
                SpriteManip::turnRight(currentTunnel);
            } else if (lastFacing == MovementComp::UP) {
                currentTunnel->changeTunnelType(Tunnel::CAP);
            }
            break;
        case MovementComp::LEFT:
            if (lastFacing == MovementComp::DOWN) {
                currentTunnel->changeTunnelType(Tunnel::CORNER);
                SpriteManip::turnLeft(currentTunnel);
            } else if (lastFacing == MovementComp::RIGHT) {
                currentTunnel->changeTunnelType(Tunnel::CAP);
                SpriteManip::turnRight(currentTunnel);
            } else if (lastFacing == MovementComp::UP) {
                currentTunnel->changeTunnelType(Tunnel::CORNER);
                SpriteManip::turnLeft(currentTunnel);
                SpriteManip::turnLeft(currentTunnel);
            }
            break;
        case MovementComp::RIGHT:
            if (lastFacing == MovementComp::DOWN) {
                currentTunnel->changeTunnelType(Tunnel::CORNER);
            } else if (lastFacing == MovementComp::LEFT) {
                currentTunnel->changeTunnelType(Tunnel::CAP);
                SpriteManip::turnLeft(currentTunnel);
            } else if (lastFacing == MovementComp::UP) {
                currentTunnel->changeTunnelType(Tunnel::CORNER);
                SpriteManip::turnRight(currentTunnel);
            }
            break;
    }
}

void BattleScene :: createTunnel(Tunnel::TunnelType stage) {
    Tunnel* newTunnel = new Tunnel(stage);
    
    // Makes the new tunnel have no width
    newTunnel->alterTextureRect(IntRect(
        newTunnel->getSprite()->getTextureRect().position,
        {50,0}
    ));
    
    // Putting tunnel in correct position and orientation
    int x = player->getTileX(), 
        y = player->getTileY();
    switch (player->getMoveComp()->isFacing()) {
        case MovementComp::UP:
            SpriteManip::turnLeft(newTunnel);
            SpriteManip::turnLeft(newTunnel);
            break;
        case MovementComp::DOWN:
            break;
        case MovementComp::LEFT:
            SpriteManip::turnRight(newTunnel);
            break;
        case MovementComp::RIGHT:
            SpriteManip::turnLeft(newTunnel);
            break;
    }
    newTunnel->setTileXY(x,y);
    tunManager->updateTunnels(newTunnel);

    currentTunnel = newTunnel;
    addObject(newTunnel);
}

void BattleScene :: update() {
    Scene::update();
    for (Enemy* en : currentEnemies) {
        en->update();
        if (!en->getIsDead()) 
            en->behave()->perform(tunManager);
    }

    // player updates
    player->update();
    
    colSystem->listen(this, currentEnemies, player);

    if (lastFacing != player->getMoveComp()->isFacing() && currentTunnel != nullptr) {
        fixTunnel();
    }
    if (player->getMoveComp()->getIsMoving()) {
        dig();
    }
    lastFacing = player->getMoveComp()->isFacing();
    playerPrevTile.x = player->getTileX();    playerPrevTile.y = player->getTileY();
}

void BattleScene :: draw(RenderWindow* window) {
    Scene::draw(window);
    player->draw(window);
    for (Enemy* en : currentEnemies) {
        en->draw(window);
    }
}

// Used to create the starting tunnels that exist to hold enemies
void BattleScene :: initializeTunnel(int x, int y, int enemyType, int type) {
    Tunnel* tunnelCap1 = new Tunnel(Tunnel::CAP);
    Tunnel* tunnelCap2 = new Tunnel(Tunnel::CAP);
    Tunnel* tunnelMiddle = new Tunnel(Tunnel::STRAIGHT);
    Enemy* newEnemy;

    // variable [ type ] refers to the tunnel's orientation (vertical or horizontal)
    switch (type) { // horizontal
        case 0:
            tunnelCap1->setTileXY(x, y);
            SpriteManip::turnLeft(tunnelCap1);
            tunManager->updateTunnels(tunnelCap1);
            
            tunnelMiddle->setTileXY(x+1, y);
            SpriteManip::turnLeft(tunnelMiddle);
            tunManager->updateTunnels(tunnelMiddle);
            
            tunnelCap2->setTileXY(x+2, y);
            SpriteManip::turnRight(tunnelCap2);
            tunManager->updateTunnels(tunnelCap2);

            newEnemy = (Enemy*)enemyMaker.create(enemyType, x+1, y);

            break;
        case 1: // vertical
            tunnelCap1->setTileXY(x, y);
            tunManager->updateTunnels(tunnelCap1);

            tunnelMiddle->setTileXY(x, y+1);
            tunManager->updateTunnels(tunnelMiddle);

            tunnelCap2->setTileXY(x, y+2);
            SpriteManip::turnRight(tunnelCap2);
            SpriteManip::turnRight(tunnelCap2);
            tunManager->updateTunnels(tunnelCap2);

            newEnemy = (Enemy*)enemyMaker.create(enemyType, x, y+1);
            break;
    }

    addObject(tunnelCap1);
    addObject(tunnelMiddle);
    addObject(tunnelCap2);
    newEnemy->behave()->makeTarget(player);
    currentEnemies.push_back(newEnemy);
}

void BattleScene :: setRoundNum(int id) {
    roundNum = id;
}