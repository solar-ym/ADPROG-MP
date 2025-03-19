#pragma once
// Originally Sir's "GD_Trn"

#include "../Objects/Tunnel.h"

class SpriteManip {
	public:
	    static void moveUp(Tunnel* obj);
	    static void moveDown(Tunnel* obj);
	    static void moveLeft(Tunnel* obj);
	    static void moveRight(Tunnel* obj);
	    static void turnLeft(Tunnel* obj);
	    static void turnRight(Tunnel* obj);
	    static void moveToRand(Tunnel* obj,int gridSize);
};
