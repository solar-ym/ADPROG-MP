#include "ACO_GameCharFactory.h"

GD_ModularObject* ACO_GameCharFactory :: makePlayer(float tileSize,int x,int y) {
    GD_ModularObject* player = new GD_ModularObject("player","crab",tileSize);
    player->setTileXY(x,y);
    player->attachComponent(new ACO_ChargeComp());
    player->attachComponent(new ACO_ColliderComp(tileSize));

    return player;
}

GD_ModularObject* ACO_GameCharFactory ::makeEnemy(int id,float tileSize, GD_ModularObject* player,int x,int y) {
    string enemyID = "enemy"+to_string(id);

    GD_ModularObject* enemy = new GD_ModularObject(enemyID,enemyID,tileSize);
    enemy->attachComponent(new ACO_EnemyAIComp(player));
    player->attachComponent(new ACO_ColliderComp(tileSize));
    enemy->setTileXY(x, y);

    return enemy;
}

GD_ModularObject* ACO_GameCharFactory ::makeSide(int id,float tileSize, GD_ModularObject* player) {
    int x = 0;
    if (id == 1) 
        x = player->getTileX()-1;
    else 
        x = player->getTileX()+1;

    GD_ModularObject* side = new GD_ModularObject("side"+to_string(id),"shot2",tileSize);
    side->setTileXY(x,player->getTileY());
    side->attachComponent(new ACO_ColliderComp(tileSize));
    player->attachChild(side);

    return side;
}

GD_ModularObject* ACO_GameCharFactory :: makeBonus(int id,float tileSize,int gridSize) {
    string str_id = "bonus"+to_string(id);

    GD_ModularObject* bonus = new GD_ModularObject(str_id,str_id,tileSize);
    bonus->attachComponent(new ACO_ColliderComp(tileSize));
    GD_Trn::moveToRand(bonus, gridSize);

    return bonus;
    
}