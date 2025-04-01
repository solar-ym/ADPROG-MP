#pragma once

#include "Component.h"

class ColliderComp: public Component{
	public:
	    ColliderComp(float tileSize);
	    float getX();
	    float getY();
	    float getWidth();
	    float getHeight();
    private:
        float tileSize;
};