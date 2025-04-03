#include "BaseEngine.h"

void BaseEngine::run(string title, unsigned int width, unsigned int height){
    window.create(VideoMode({width, height}), title);
    window.setFramerateLimit(60);
    
    //Initialize the game
    init();

    Clock clock;
    Time timestamp = Time::Zero;

    while (window.isOpen()){
        while(const optional event = window.pollEvent()){
            if(event->is<Event::Closed>())
                 window.close();
            else if(const auto* keyPressed=event->getIf<Event::KeyPressed>())
                keyPressTrigger(keyPressed->scancode);
            else if(const auto* keyPressed=event->getIf<Event::KeyReleased>())
                keyReleaseTrigger(keyPressed->scancode);
        }//end while

        timestamp += clock.restart();
        while(timestamp>TimePerFrame){
            timestamp -= TimePerFrame;
            update(TimePerFrame);
        }

        window.clear();
        draw(&window);
        window.display();
    }//end while
}//end func
