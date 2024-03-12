//
// Created by Victor Navarro on 15/02/24.
//

#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(string _name, int _health, int _attack, int _defense, int _speed) : Character(_name, _health, _attack, _defense, _speed, true) {
    level = 1;
    experience = 0;
}

void Player::doAttack(Character *target) {
    target->takeDamage(attack);
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;

    health-= trueDamage;

    cout << name << " took " << trueDamage << " damage!" << endl;

    if(health <= 0) {
        cout << name << " has been defeated!" << endl;
    }
}

void Player::levelUp() {
    level++;
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 100-experience;
    }
}

Character* Player::selectTarget(vector<Enemy*> possibleTargets) {
    //va a recibir un vector de enemigos que son posibles blancos de ataque
    int selectedTarget = 0;//inicia en cero
    cout << "Select a target: " << endl;//se elije un enemigo
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". " << possibleTargets[i]->getName() << endl;//obtenemos el nombre
    }

    //TODO: Add input validation
    cin >> selectedTarget;
    return possibleTargets[selectedTarget];
}

Action Player::takeAction(vector<Enemy*> enemies) {//funcion para elegir que accion realizar
    int action = 0;//inicia la variable en 0
    cout << "Select an action: " << endl
    << "1. Attack" << endl;

    //TODO: Validate input
    cin >> action;
    Action currentAction;//crear un objeto de accion, para eso se creo el constructo vacio
    Character* target = nullptr;

    switch(action) {
        case 1:
            target = selectTarget(enemies);//mandamos a llamra la funcion que selecciona a quien atacar
            currentAction.target = target;//se le asigna el mismo valor de target
            currentAction.action = [this, target](){//es un puntero a una funcion, le estoy diciendo que la guarde en action
                doAttack(target);
            };
            currentAction.speed = getSpeed();//se le asigna velocidad del personaje actual
            break;
        default:
            cout << "Invalid action" << endl;
            break;
    }

    return currentAction;
}