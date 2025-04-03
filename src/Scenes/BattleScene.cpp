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
    cout << "Attempting to load Battle Screen" << endl;

    roundData = dataLoader.loadData(roundNum);

    cout << "[BATTLE SCREEN] Round data loaded" << endl;
    cout << "   > roundData size: " << roundData.size() << endl;
    
    Background* bg  = new Background("BG1_norm");
    cout << "[BATTLE SCREEN] Background created" << endl;
    addObject(bg);
    cout << "[BATTLE SCREEN] Background pushed" << endl;

    // TUNNELS
    for (int i = 0; i < roundData.size(); i += 4) {
        initializeTunnel(roundData[i], roundData[i+1], roundData[i+2], roundData[i+3]);
    }

    cout << "[BATTLE SCREEN] Objects pushed" << endl;
    cout << "Objects: " << getAllObjects().size() << endl;
}

void BattleScene :: onUnload() {
    removeAllObjects();
    if (!roundData.empty()) {
        roundData.clear();
    }
    // for (int i = 0; i < DIRT_HEIGHT; i++) {
    //     for (int j = 0; j < DIRT_WIDTH; j++) {
    //         status[i][j] = 0;
    //     }
    // }
    tunManager->fullReset();
    lastFacing = MovementComp::RIGHT;
    currentEnemies.clear();
    delete currentTunnel;
    delete colSystem;
}

void BattleScene :: reloadRoundData() {
    getAllObjects().clear();

    Background* bg  = new Background("BG1_norm");
    cout << "[BATTLE SCREEN] New background created" << endl;
    addObject(bg);

    if (!roundData.empty()) {
        roundData.clear();
    }

    // for (int i = 0; i < DIRT_HEIGHT; i++) {
    //     for (int j = 0; j < DIRT_WIDTH; j++) {
    //         status[i][j] = 0;
    //     }
    // }
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
    // if (currentTunnel == nullptr && status[player->getTileY()][player->getTileX()] == 0) {
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
    cout << "[ BATTLE SCENE ] Trying to fix tunnel." << endl;

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
    // status[y][x] = newTunnel->getTunnelType();
    tunManager->updateTunnels(newTunnel);

    currentTunnel = newTunnel;
    addObject(newTunnel);
}

void BattleScene :: update() {
    Scene::update();
    cout << "Objects updated." << endl;
    for (Enemy* en : currentEnemies) {
        en->update();
        cout << "Enemy updated." << endl;
        if (!en->getIsDead()) 
            en->behave()->perform(tunManager);
    }
    cout << "Enemies updated." << endl;

    // player updates
    player->update();
    cout << "Player updated." << endl;
    
    colSystem->listen(this, currentEnemies, player);
    cout << "Objects updated." << endl;

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
            // status[y][x] = tunnelCap1->getTunnelType();
            SpriteManip::turnLeft(tunnelCap1);
            tunManager->updateTunnels(tunnelCap1);
            
            tunnelMiddle->setTileXY(x+1, y);
            // status[y][x+1] = tunnelMiddle->getTunnelType();
            SpriteManip::turnLeft(tunnelMiddle);
            tunManager->updateTunnels(tunnelMiddle);
            
            tunnelCap2->setTileXY(x+2, y);
            // status[y][x+2] = tunnelCap2->getTunnelType();
            SpriteManip::turnRight(tunnelCap2);
            tunManager->updateTunnels(tunnelCap2);

            newEnemy = (Enemy*)enemyMaker.create(enemyType, x+1, y);

            break;
        case 1: // vertical
            tunnelCap1->setTileXY(x, y);
            // status[y][x] = tunnelCap1->getTunnelType();
            tunManager->updateTunnels(tunnelCap1);

            tunnelMiddle->setTileXY(x, y+1);
            // status[y+1][x] = tunnelMiddle->getTunnelType();
            tunManager->updateTunnels(tunnelMiddle);

            tunnelCap2->setTileXY(x, y+2);
            // status[y+2][x] = tunnelCap2->getTunnelType();
            SpriteManip::turnRight(tunnelCap2);
            SpriteManip::turnRight(tunnelCap2);
            tunManager->updateTunnels(tunnelCap2);

            newEnemy = (Enemy*)enemyMaker.create(enemyType, x, y+1);

            break;
        default: 
            cout << "[ BATTLE SCENE ] Tunnel Creation failed. Invalid tunnel orientation." << endl;
            cout << "   > Orientation recieved: " << type << endl;
            break;
    }

    addObject(tunnelCap1);
    addObject(tunnelMiddle);
    addObject(tunnelCap2);
    currentEnemies.push_back(newEnemy);

    cout << "[ BATTLE SCENE ] Tunnels pushed." << endl;
}