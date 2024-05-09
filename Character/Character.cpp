//
// Created by Victor Navarro on 15/02/24.
//

#include "Character.h"
Character::Character(string _name, int _health, int _OgHealth, int _attack, int _defense, int _speed, bool _isPlayer) {
    name = _name;
    health = _health;
    OgHealth= _OgHealth;//valor de referencia de salud inicial
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
}

string Character::getName() {
    return name;
}

int Character::getHealth() {
    return health;
}

int Character::getOgHealth() {
    return OgHealth;
}

int Character::getAttack() {
    return attack;
}

double Character::getDefense() {
    if(isDefending){//si el personaje se esta defendiendo
        return defense*1.20;//hago esta multiplicacion para que su defensa aumente un 20% en el turno
    }
    return defense;//si no se esta defendiendo solo entrego la defensa normal
}

int Character::getSpeed() {
    return speed;
}

string Character::toString() {
    return "Name: " + name + "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed);
}

bool Character::getIsPlayer() {//definir si es jugador o enemigo
    return isPlayer;
}

bool Character::flee(Character*target) {
    if(this->speed > target->speed)//si nuestro personaje tiene mayor velocidad que el oponente siempre puede escapar
        return true;

    int chance = rand() % 100;//si no es mas rapido hya una probabailidad de que pueda escapar
    /*"rand() % 100" genera una numero aleatorio entre cero y cien*/
    return chance > 30;//si el chance es mayor a 30 si puede escapar
    //una comparacion retorna true or false
}

void Character::doDefense() {//estoy definiendo si hace la accion de defender
    isDefending=true;
}
