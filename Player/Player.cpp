//
// Created by Victor Navarro on 15/02/24.
//

#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(string _name, int _health, int _OgHealth, int _attack, int _defense, int _speed) : Character(_name, _health, _OgHealth, _attack, _defense, _speed, true) {
    level = 1;
    experience = 0;
}

void Player::doAttack(Character *target) {
    target->takeDamage(attack);
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - getDefense();

    health -= trueDamage;

    cout << name << " took " << trueDamage << " damage!" << endl;
    cout <<"remainig health " + to_string(this->getHealth())<<endl;

    if (health <= 0) {
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

Action Player::takeAction(vector<Enemy *> enemies) {//IMPORTANTE! FUNCION PARA DEFINIR QUE ACCION REALIZAR
    isDefending=false;//primero la accion de defensa es un false
    int action = 0;//inicia la variable en 0
    cout << "Select an action: " << endl
         << "1. Attack" << endl
         << "2. Defend" << endl;//agrego la opcion para que el jugador se pueda defender

    //TODO: Validate input
    cin >> action;
    Action currentAction;//crear un objeto de accion, para eso se creo el constructo vacio
    Character *target = nullptr;

    switch (action) {
        case 1:
            target = selectTarget(enemies);//mandamos a llamra la funcion que selecciona a quien atacar
            currentAction.target = target;//se le asigna el mismo valor de target
            currentAction.action = [this, target]() {//es un puntero a una funcion, le estoy diciendo que la guarde en action
                doAttack(target);
            };
            currentAction.speed = getSpeed();//se le asigna velocidad del personaje actual
            break;
        case 2://decido defenderme
            currentAction.target = nullptr;//a fuerza tiene que tener una valor target porque evalua la vida, asi que le pongo que soy yo
            currentAction.action = [this]() {//es un puntero a una funcion, le estoy diciendo que la guarde en action y cuando decido defender se ejecuta el doDefense
                doDefense();//el personaje se va a defender
                cout << "Defense is being implemented"<<endl;
            };
            currentAction.speed = 999999;//se le asigna velocidad muy alta para que el personaje siempre se pueda defender

            break;
        default:
            cout << "Invalid action" << endl;
            break;
    }

    return currentAction;
}