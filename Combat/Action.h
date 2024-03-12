//
// Created by Victor Navarro on 29/02/24.
//

#ifndef RPG_ACTION_H
#define RPG_ACTION_H
#include <functional>
#include "../Character/Character.h"

using namespace std;

class Action {
public:
    //velocidad de quien realiza la accion
    int speed = 0;

    //Quien recibe de la accion
    Character* target = nullptr;

    //Quien realiza la accion
    Character* subscriber = nullptr;

    //Puntero a una función que no recibe parametros y no devuelve nada
    function<void(void)> action = nullptr;//es una funcion que va a ser ejecutada en algun momento
    //y la estamos guardando en una variable
    Action(int _speed, function<void(void)> _action, Character* _subscriber, Character* _target);
    Action();//se deja vacio para poder hacer mas declaraciones, linea 63 player.cpp

    bool operator<(const Action& other) const;
};


#endif //RPG_ACTION_H
