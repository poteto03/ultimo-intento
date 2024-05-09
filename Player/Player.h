//
// Created by Victor Navarro on 15/02/24.
//
#pragma once//para resolver la dependencia ciclica
#ifndef RPG_PLAYER_H
#define RPG_PLAYER_H
#include "../Character/Character.h"
#include "../Enemy/Enemy.h"
#include "../Combat/Action.h"
#include <vector>

class Enemy;

class Player: public Character {
    //TODO: Implement Classes (Mage, Warrior, Rogue, etc..)
    //TODO: Implement Inventory
private:
    int level;
    int experience;

    void levelUp();
public:
    Player(string _name, int _health, int _OgHealth, int _attack, int _defense, int _speed);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    Character* selectTarget(vector<Enemy*> possibleTargets);//para seleccionar un blaco de la lista de enemigos
    Action takeAction(vector<Enemy*> enemies);//funcion que retorna una actccion, se llama takeAction y recive un vector de enemigos

    void gainExperience(int exp);

    //TODO: Implement use object
};


#endif //RPG_PLAYER_H
