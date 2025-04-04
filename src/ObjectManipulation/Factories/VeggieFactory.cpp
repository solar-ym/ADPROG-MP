#include "VeggieFactory.h"

Entity* VeggieFactory::create(int id, int x, int y) {
    Veggie* newVeggie;
    switch (id) {
        case CARROT: newVeggie = new Veggie("VEG_carrot");
            break;
        case TURNIP: newVeggie = new Veggie("VEG_turnip");
            break;
        case MUSHROOM: newVeggie = new Veggie("VEG_mushroom");
            break;
        case LEEK: newVeggie = new Veggie("VEG_leek");
            break;
        case EGGPLANT: newVeggie = new Veggie("VEG_eggplant");
            break;
        case PEPPER: newVeggie = new Veggie("VEG_pepper");
            break;
        case TOMATO: newVeggie = new Veggie("VEG_tomato");
            break;
        case GARLIC: newVeggie = new Veggie("VEG_garlic");
            break;
    }
    
    //Set the tile it spawns in (this is the same for all of them)
    newVeggie->setTileXY(x, y);
    //Add a collision component
    newVeggie->addComponent(new ColliderComp(TILE_SIZE));
    newVeggie->setTimer(20); //sets how long the veggie can stay on the ground
    newVeggie->setEnabled(false);

    return newVeggie;
}