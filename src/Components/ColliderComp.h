#pragma once

#include "Component.h"
#include "../Objects/Entity.h"

class ColliderComp: public Component{
	public:
	    ColliderComp(float tileSize);
	    void perform(sf::Time deltaTime);
	    float getX();
	    float getY();
	    float getWidth();
	    float getHeight();
    private:
        float tileSize;
};