//
// Created by Victor Navarro on 15/02/24.
//

#include "Enemy.h"
#include "../Utils.h"
#include <iostream>


using namespace std;
using namespace combat_utils;

Enemy::Enemy(string _name, int _health, int _attack, int _defense, int _speed, int _experience) : Character(_name, _health, _attack, _defense, _speed, false) {
    experience = _experience;
}

void Enemy::doAttack(Character *target) {
    target->takeDamage(getRolledAttack(attack));
}

void Enemy::takeDamage(int damage) {
    int trueDamage = damage - defense;
    health-= trueDamage;

    cout << name << " took " << trueDamage << " damage!" << endl;
    if(health <= 0) {
        cout << name << " has been defeated!" << endl;
    }
}

int Enemy::getExperience() {
    return experience;
}

Character* Enemy::selectTarget(vector<Player*> possibleTargets) {
    //target with less health
    int lessHealth = 9999999;//todos los personaje van a tener menos de esta vida
    Character* target = nullptr;
    for(auto character : possibleTargets) {//iteramostodo el vector de posibles objetos
        if(character->getHealth() < lessHealth) {
            lessHealth = character->getHealth();//actualizamos la vida mas baja que hay
            target = character;//y hacemos que el puntero apunte al personaje con la vida mas baja
        }
    }
    return target;//y retonamos al caracter con menos vida
}

Action Enemy::takeAction(vector<Player*> partyMembers) {//recibe la lista de jugadores para decidir a quien atacar
    Action currentAction;
    currentAction.speed = getSpeed();//asignamos velocidad

    Character* target = selectTarget(partyMembers);//llamamos la funcion selectTarget que es para atacar a quien tiene menos vida
    currentAction.target = target;
    currentAction.action = [this, target](){//hacemos lo mismo que en player le pasamos el this el target para que pueda atacar
        doAttack(target);
    };

    return currentAction;
}