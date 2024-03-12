//
// Created by Victor Navarro on 15/02/24.
//

#ifndef RPG_ENEMY_H
#define RPG_ENEMY_H

#pragma once//para resolver la dependenciaciclica
#include "../Character/Character.h"
#include "../Player/Player.h"
#include <vector>
#include "../Combat/Action.h"

class Player;

class Enemy: public Character{
private:
    int experience;
public:
    Enemy(string _name, int _health, int _attack, int _defense, int _speed, int _experience);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    Character* selectTarget(vector<Player*> possibleTargets);//para selecconar un blanco de la lista de jugadores
    Action takeAction(vector<Player*> partyMembers);//recibe el vector de jugadores y va a realizar la acccion

    int getExperience();
};


#endif //RPG_ENEMY_H
