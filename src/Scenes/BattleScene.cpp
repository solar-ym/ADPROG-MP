#include "BattleScene.h"

BattleScene :: BattleScene(string name, int roundNum, Drillku* player) : Scene(name) {
    roundData.clear();
    this->roundNum = roundNum;
    this->player = player;

    colSystem = new CollisionSystem();
    tunManager = new TunnelManager();
}

void BattleScene :: onLoad() {
    roundData = dataLoader.loadData(roundNum);
    prevRoundNum = roundNum;

    Background* bg  = new Background("BG1_norm", 2);
    addObject(bg);

    UIAsset* livesText = new UIAsset("UI_lives", 
                                {TILE_SIZE * DIRT_WIDTH, 
                                TILE_SIZE * (SKY_HEIGHT-1)});
    addObject(livesText);

    for(int i = 0; i < 6; i++){
        if(i < 3)  
        noOfLives.push_back(new UIAsset("UI_livesIcon", 
                                    {TILE_SIZE * (DIRT_WIDTH+i), 
                                    TILE_SIZE * (SKY_HEIGHT)}));
        else
        noOfLives.push_back(new UIAsset("UI_livesIcon", 
                {TILE_SIZE * (DIRT_WIDTH+(i%3)), 
                TILE_SIZE * (SKY_HEIGHT+1)}));
    }

    //UI Assets
    uiNextRound = new UIAsset("UI_nextRound",
                            {TILE_SIZE * DIRT_WIDTH, 
                            TILE_SIZE * (DIRT_HEIGHT)});
    uiPressK = new UIAsset("UI_K",
                        {TILE_SIZE * DIRT_WIDTH, 
                        TILE_SIZE * (DIRT_HEIGHT-1)});

    // TUNNELS
    initStartTunnel();
    for (int i = 0; i < roundData.size(); i += 4) {
        initializeTunnel(roundData[i], roundData[i+1], roundData[i+2], roundData[i+3]);
    }

    // FIRST FLOWER
    currentFlowers.push_back(new Flower(Flower::BUD));
    currentFlowers.back()->setTileXY(9, 1);

    // VEGGIES
    for(int i = VeggieFactory::CARROT; i <= VeggieFactory::GARLIC; i++){
        //Create all of the veggies
        currentVeggies.push_back(dynamic_cast<Veggie*>(veggieMaker.create(i, 6, 5)));
    }

    roundVeggie = currentVeggies[VeggieFactory::CARROT];
    makeRocks();
}

void BattleScene :: onUnload() {
    removeAllObjects();

    if (!roundData.empty()) {
        roundData.clear();
    }

    tunManager->fullReset();

    lastFacing = MovementComp::RIGHT;
    if (!currentEnemies.empty())
        currentEnemies.clear();

    for(UIAsset* livesIcon : noOfLives)
        delete livesIcon;

    if (!noOfLives.empty())
        noOfLives.clear();

    for(Flower* flower : currentFlowers)
        delete flower;

    if (!currentFlowers.empty())
        currentFlowers.clear();

    for(Veggie* veggie : currentVeggies)
        delete veggie;

    if (!currentVeggies.empty())
        currentVeggies.clear();

    for (Rock* rock : currentRocks)
        delete rock;

    if (!currentRocks.empty())
        currentRocks.clear();

    // Player reset
    player->setTileXY(6,5);
    player->setIsDying(false);
}

void BattleScene :: reloadRoundData() {
    getAllObjects().clear();

    if (roundNum < 5) {
        Background* bg  = new Background("BG1_norm", 2);
        addObject(bg);

        //Adds a bud flower
        //Basically  on load it pushes back a new flower into the vector
        //Then when its like rounds 2->4, it gets the tile x and tile y (tho y doesnt matter but more dynamic ig)
        //then it pushes back a new flower with that tile x - 2 (since they go to each other's left)
        //We only want 4 flowers for the first four rounds
        if(prevRoundNum != roundNum){
            int flowerXPos, flowerYPos; 
            flowerXPos = currentFlowers.back()->getTileX() - 2;
            flowerYPos = currentFlowers.back()->getTileY();
            currentFlowers.push_back(new Flower(Flower::BUD));
            currentFlowers.back()->setTileXY(flowerXPos, flowerYPos);
        }

    } else if (roundNum > 8) {
        Background* bg  = new Background("BG3_norm", 2);
        addObject(bg);

        //If the current one is a mid stage, turn into a bloom
        if(prevRoundNum != roundNum){
            for(int i = 0; i < currentFlowers.size(); i++){
                if(currentFlowers[i]->getFlowerStage() == Flower::MID){
                    int flowerXPos, flowerYPos; 
                    flowerXPos = currentFlowers[i]->getTileX();
                    flowerYPos = currentFlowers[i]->getTileY();
                
                    currentFlowers[i]->changeTexture(Flower::BLOOM);
                    currentFlowers[i]->setTileXY(flowerXPos, flowerYPos);
                    break;
                }
            }
        }
    } else {
        Background* bg  = new Background("BG2_norm", 2);
        addObject(bg);

        //If the current one is a bud, then change current one to mid and then break
        if(prevRoundNum != roundNum){
            for(int i = 0; i < currentFlowers.size(); i++){
                if(currentFlowers[i]->getFlowerStage() == Flower::BUD){
                    int flowerXPos, flowerYPos; 
                    
                    flowerXPos = currentFlowers[i]->getTileX();
                    flowerYPos = currentFlowers[i]->getTileY();
                
                    currentFlowers[i]->changeTexture(Flower::MID);
                    currentFlowers[i]->setTileXY(flowerXPos, flowerYPos);
                    break;
                }
            }
        }
    }

    if (!roundData.empty()) {
        roundData.clear();
    }

    tunManager->fullReset();

    currentTunnel = nullptr;
    lastFacing = MovementComp::RIGHT;
    currentEnemies.clear();
    
    roundData = dataLoader.loadData(roundNum);
    
    initStartTunnel();
    for (int i = 0; i < roundData.size(); i += 4) {
        initializeTunnel(roundData[i], roundData[i+1], roundData[i+2], roundData[i+3]);
    }

    player->setTileXY(6,5);

    //Reload veggies when moving onto the next round
    for(int i = 0; i < currentVeggies.size(); i++){
        if(currentVeggies[i]->getEnabled()){
            currentVeggies[i]->setEnabled(false);
            currentVeggies[i]->setTileXY(6,5);
            break;
        }
    }

    switch(roundNum){
        case 1: // ROUND 1 - CARROT
            roundVeggie = currentVeggies[VeggieFactory::CARROT];
            break;
        case 2: // ROUND 2 - TURNIP
            roundVeggie = currentVeggies[VeggieFactory::TURNIP];
            break;
        case 3: // ROUND 3 - MUSHROOM
            roundVeggie = currentVeggies[VeggieFactory::MUSHROOM];
            break;
        case 4: // ROUND 4-5 - LEEK
        case 5: 
            roundVeggie = currentVeggies[VeggieFactory::LEEK];
            break;
        case 6: // ROUND 6-7 - EGGPLANT
        case 7:
            roundVeggie = currentVeggies[VeggieFactory::EGGPLANT];
            break;
        case 8: // ROUND 8-9 - PEPPER
        case 9:
            roundVeggie = currentVeggies[VeggieFactory::PEPPER];
            break;
        case 10: // ROUND 10-11 - TOMATO
        case 11:
            roundVeggie = currentVeggies[VeggieFactory::TOMATO];
            break;
        case 12: // ROUND 12 - GARLIC
            roundVeggie = currentVeggies[VeggieFactory::GARLIC];
            break;
    }

    currentRocks.clear();
    makeRocks();
    droppedRocks = 0;

    prevRoundNum = roundNum;
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
    player->update();

    colSystem->listen(this, currentEnemies, player, tunManager);

    if (!(player->getIsDying())) {
        Scene::update();
        for (Enemy* en : currentEnemies) {
            en->update();
            if (!en->getIsDead() && !en->getIsDying()) 
                en->behave()->perform(tunManager);
        }
        int n = 0;
        for (Rock* rock: currentRocks) {
            rock->update();
            if (rock->getRunning())
                n++;
        }
        droppedRocks = n;
    }

    if (lastFacing != player->getMoveComp()->isFacing() && currentTunnel != nullptr) {
        fixTunnel();
    }
    if (player->getMoveComp()->getIsMoving()) {
        dig();
    }
    lastFacing = player->getMoveComp()->isFacing();
    playerPrevTile.x = player->getTileX();    playerPrevTile.y = player->getTileY();

    if(droppedRocks >= 3) {
        roundVeggie->setEnabled(true);
    }
}

void BattleScene :: draw(RenderWindow* window) {
    Scene::draw(window);
    if(getAliveEnemies() == 0){
        uiNextRound->draw(window);
        uiPressK->draw(window);
    }
    for(int i = 0; i < player->getLives(); i++)
        noOfLives[i]->draw(window);
    for (Enemy* en : currentEnemies) 
        en->draw(window);
    for (Flower* flower : currentFlowers)
        flower->draw(window);
    roundVeggie->draw(window);
    for (Rock* rock: currentRocks)
        rock->draw(window);

    player->draw(window);
}

void BattleScene :: initStartTunnel(){
    for(int i = 0; i < 5; i++){
        Tunnel* straight = new Tunnel(Tunnel::STRAIGHT);
        straight->setTileXY(6, i);

        tunManager->updateTunnels(straight);

        addObject(straight);
    }

    Tunnel* tunnelCap1 = new Tunnel(Tunnel::CAP);
    Tunnel* tunnelCap2 = new Tunnel(Tunnel::CAP);
    Tunnel* tunnelMiddle = new Tunnel(Tunnel::STRAIGHT);

    tunnelCap1->setTileXY(5, 5);
    SpriteManip::turnLeft(tunnelCap1);
    tunManager->updateTunnels(tunnelCap1);
    
    tunnelMiddle->setTileXY(6, 5);
    SpriteManip::turnLeft(tunnelMiddle);
    tunManager->updateTunnels(tunnelMiddle);
    
    tunnelCap2->setTileXY(7, 5);
    SpriteManip::turnRight(tunnelCap2);
    tunManager->updateTunnels(tunnelCap2);

    addObject(tunnelCap1);
    addObject(tunnelCap2);
    addObject(tunnelMiddle);
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

void BattleScene :: makeRocks() {
    currentRocks.clear();
    int n = MovementComp::randomize(3, 5);

    for (int i = 0; i < n; i++) {
        int x = MovementComp::randomize(0, DIRT_WIDTH-1);
        int y = MovementComp::randomize(0, DIRT_HEIGHT-2);

        while (tunManager->hasTunnel(x, y) || tunManager->hasTunnel(x, y+1)) {
            x = MovementComp::randomize(0, DIRT_WIDTH-1);
            y = MovementComp::randomize(0, DIRT_HEIGHT-2);
        }

        currentRocks.push_back(new Rock(x, y, tunManager));
    }
}

int BattleScene::getAliveEnemies(){
    int countAlive = 0;
    for(int i = 0; i < currentEnemies.size(); i++)
        if(!(currentEnemies[i]->getIsDead())) countAlive++;
    
    return countAlive;
}

void BattleScene :: setRoundNum(int id) {
    roundNum = id;
}

Veggie* BattleScene :: getRoundVeggie(){
    return roundVeggie;
}

vector<Rock*> BattleScene :: getAllRocks() {
    return currentRocks;
}

BattleScene :: ~BattleScene() {
    delete currentTunnel;
    delete colSystem;
}
