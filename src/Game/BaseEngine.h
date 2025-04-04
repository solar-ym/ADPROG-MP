#pragma once

#include "../Utility/configurations.h"

class BaseEngine{
    private:
        RenderWindow window;
    protected:
        const Time TimePerFrame = seconds(1.0f / 60.0f);
    public:
        virtual void init() = 0;
        virtual void update(Time deltaTime) = 0;
        virtual void draw(RenderWindow *window) = 0;
        virtual void keyPressTrigger(Keyboard::Scan keyCode, RenderWindow *window) = 0;
        virtual void keyReleaseTrigger(Keyboard::Scan keyCode) = 0;
        void run(string title, unsigned int width, unsigned int height);
};
