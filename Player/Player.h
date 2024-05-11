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
    void saveProgress();

public:
    Player(char* _name, int _health, int _attack, int _defense, int _speed);
    Player(char* _name, int _health, int _attack, int _defense, int _speed, bool isPlayer, bool isDefending, int _level, int _experience);
    void doAttack(Character *target) override;
    void takeDamage(int damage) override;
    Character* selectTarget(vector<Enemy*> possibleTargets);//para seleccionar un blaco de la lista de enemigos
    Action takeAction(vector<Enemy*> enemies);//funcion que retorna una actccion, se llama takeAction y recive un vector de enemigos
    char* serialize();//para serializar
    static Player* unserialize(char*buffer);

    void gainExperience(int exp);

    static const unsigned int BUFFER_SIZE= sizeof (name)+sizeof (health)+ sizeof(attack)+ sizeof(defense)+ sizeof(isPlayer)+
                                                                                                    sizeof(isDefending)+
                                                                                                    sizeof(level)+
                                                                                                    sizeof(experience);

    //TODO: Implement use object
private:
    char buffer[Player::BUFFER_SIZE];
};


#endif //RPG_PLAYER_H