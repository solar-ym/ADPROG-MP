#pragma once

#include "../Objects/Entity.h"
#include "../Objects/Enemies/Enemy.h"
#include "../Objects/Veggie.h"

class EntityFactory {
    public:
        virtual Entity* create(int id) = 0;
};

class EnemyFactory : public EntityFactory {
    public:
        enum enemyType {POOKIE, GEYGAR};
        
        Entity* create(enemyType id) {
            Enemy* newEnemy;
            switch (id) {
                case POOKIE: 
                    newEnemy = new Enemy("Pookie", "POOKIE_walk1");
                    break;
                case GEYGAR: 
                    newEnemy = new Enemy("Geygar", "GEYGAR_walk1");
                    break;
            }
            return newEnemy;
        }
};

class VeggieFactory : public EntityFactory {
    public:
        enum VegType {CARROT, EGGPLANT, GARLIC, LEEK,
                      MUSHROOM, PEPPER, TOMATO, TURNIP};

        Entity* create(int id) {
            Veggie* newVeggie;
            switch (id) {
                case CARROT: 
                    newVeggie = new Veggie("VEG_carrot");
                    break;
                case EGGPLANT: 
                    newVeggie = new Veggie("VEG_eggplant");
                    break;
                case GARLIC: 
                    newVeggie = new Veggie("VEG_garlic");
                    break;
                case LEEK: 
                    newVeggie = new Veggie("VEG_leek");
                    break;
                case MUSHROOM: 
                    newVeggie = new Veggie("VEG_mushroom");
                    break;
                case PEPPER: 
                    newVeggie = new Veggie("VEG_pepper");
                    break;
                case TOMATO: 
                    newVeggie = new Veggie("VEG_tomato");
                    break;
                case TURNIP: 
                    newVeggie = new Veggie("VEG_turnip");
                    break;
            }
            return newVeggie;
        }
};

class RockFactory : public EntityFactory {

};