#pragma once
// Originally Sir's "GD_Trn"

#include "../Objects/Entity.h"

class SpriteManip {
	public:
	    static void moveUp(Entity* obj);
	    static void moveDown(Entity* obj);
	    static void moveLeft(Entity* obj);
	    static void moveRight(Entity* obj);
	    static void turnLeft(Entity* obj);
	    static void turnRight(Entity* obj);
	    static void moveToRand(Entity* obj,int gridSize);
};
