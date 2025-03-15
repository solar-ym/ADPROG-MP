#pragma once

#include "GD_ModularObject.h"
#include "ACO_ChargeComp.h"
#include "ACO_ColliderComp.h"
#include "ACO_CharHealthComp.h"
#include "ACO_EnemyAIComp.h"

#define SIDE01_IDX 3
#define SIDE02_IDX 4
#define PLAYER_IDX 5
#define BONUS1_IDX 6
#define BONUS2_IDX 7

using namespace std;
using namespace sf;

class ACO_GameCharFactory{
	public:
	    static GD_ModularObject* makePlayer(float tileSize,int x,int y);
	    static GD_ModularObject* makeEnemy(int id,float tileSize,
	        GD_ModularObject* player,int x,int y);
	    static GD_ModularObject* makeSide(int id,float tileSize,
	        GD_ModularObject* player);
	    static GD_ModularObject* makeBonus(int id,float tileSize,int gridSize);
};
