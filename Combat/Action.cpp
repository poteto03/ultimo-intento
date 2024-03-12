//
// Created by Victor Navarro on 29/02/24.
//
/*Para que do combat no tenga una programacion spaguetti toda fea se hace una abstreaccion
 * Se crea una nueva clase*/
#include "Action.h"
//para inicializarlo
Action::Action(int _speed, std::function<void(void)> _action, Character* _subscriber, Character* _target) {
    speed = _speed;//velocidad del participante
    action = _action;
    target = _target;
    subscriber = _subscriber;
}

Action::Action() {//para inicializarlo
    speed = 0;
    action = nullptr;
    target = nullptr;
    subscriber = nullptr;
}

bool Action::operator<(const Action &other) const {//definimos que va a ordenar las velocidades
    return speed < other.speed;
}