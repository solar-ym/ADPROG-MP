#pragma once

#include "../Utility/configurations.h"

class GameObject {
	private:
		string name;
	public:
        GameObject() {}
        GameObject(string objName) {
            name = objName;
        }
	    string getName() {
            return name;
        }
		virtual void initialize() = 0;
        virtual void update() = 0;
        virtual void draw(RenderWindow *window) = 0;
};