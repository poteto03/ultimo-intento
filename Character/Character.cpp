//
// Created by Victor Navarro on 15/02/24.
//

#include "Character.h"
#include <string.h>
Character::Character(char* _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer) {
    strcpy(name, _name);
    health = _health;
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
}

char* Character::getName() {
    return name;
}

int Character::getHealth() {
    return health;
}

int Character::getAttack() {
    return attack;
}

int Character::getDefense() {
    if(isDefending){//si el personaje se esta defendiendo
        return defense*1.20;//hago esta multiplicacion para que su defensa aumente un 20% en el turno
    }
    return defense;//si no se esta defendiendo solo entrego la defensa normal
}

int Character::getSpeed() {
    return speed;
}

string Character::toString() {
    return "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed);
}

bool Character::getIsPlayer() {//definir si es jugador o enemigo
    return isPlayer;
}

bool Character::flee(Character*target) {
    if(this->speed > target->speed)//si nuestro personaje tiene mayor velocidad que el oponente siempre puede escapar
        return true;

    int chance = rand() % 100;//si no es mas rapido hya una probabailidad de que pueda escapar
    /*"rand() % 100" genera una numero aleatorio entre cero y cien*/
    return chance > 40;//si el chance es mayor a 40 si puede escapar
    //una comparacion retorna true or false
}

void Character::doDefense() {//estoy definiendo si hace la accion de defender
    isDefending=true;
}

void Character::setHealth(int _health) {//para establecer un nuevo valor de salud al aumentar
    //los valores de las estadisticas creo este void que me permite asignarla y modificar el valor
    //y asi con los valores de ataque, defensa y velocidad
    health = _health;
}

void Character::setAttack(int _attack)  {//para establecer un nuevo valor de ataque
    attack = _attack;
}

void Character::setDefense(int _defense) {//para establecer un nuevo valor de defensa
    defense = _defense;
}

void Character::setSpeed(int _speed) {//para establecer un nuevo valor de velocidad
    speed = _speed;
}