//
// Created by Victor Navarro on 15/02/24.
//

#include "Enemy.h"
#include "../Utils.h"
#include <iostream>


using namespace std;
using namespace combat_utils;

Enemy::Enemy(char* _name, int _health, int _attack, int _defense, int _speed, int _experience) : Character(_name, _health, _attack, _defense, _speed, false) {
    experience = _experience;
    OgHealth=health;
}

void Enemy::doAttack(Character *target) {
    target->takeDamage(getRolledAttack(attack));
}

void Enemy::takeDamage(int damage) {
    int trueDamage = damage - getDefense();
    health-= trueDamage;

    cout << name << " took " << trueDamage << " damage!" << endl;
    cout <<"remainig health " + to_string(this->getHealth())<<endl;
    if(health <= 0) {
        cout << name << " has been defeated!!" << endl;
    }
}

const int Enemy::getOgHealth(){
    return OgHealth;
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

    isDefending=false;//primero la accion de defensa es un false
    Action currentAction;
    currentAction.speed = getSpeed();//asignamos velocidad

    Character* target = selectTarget(partyMembers);//llamamos la funcion selectTarget que es para atacar a quien tiene menos vida
    //aqui hacer la defensa del villano
    int referenceHealth=this->getOgHealth()*0.15;//variable para saber el 15% del valor de la vida original del villano
    //cout<<"\nreference health is " + to_string(referenceHealth);
    //cout<<"\nget health" + to_string(this->getHealth());
    if(this->getHealth()<referenceHealth){//si la salud actual es de menos del 15%
        int EnemyDefenseProp =rand() % 100 +1;//aqui establesco la probabilidad de que el villano se defienda, genero un numero del 1 al 100
        cout<<"\nEnemyDefenseProp is " + to_string(EnemyDefenseProp);
        //int EnemyDefenseProp = 30;//aqui establesco la probabilidad de que el villano se defienda, genero un numero del 1 al 100

        if (EnemyDefenseProp>40){//si este numero es mayor a cuarenta, porque hay un 40% de provabilidad de que se defienda
            cout << "Defense process"<<endl;
            currentAction.target = nullptr;//a fuerza tiene que tener una valor target porque evalua la vida, asi que le pongo que soy yo
            currentAction.action = [this]() {//es un puntero a una funcion, le estoy diciendo que la guarde en action y cuando decido defender se ejecuta el doDefense
                doDefense();//el personaje se va a defender
                cout << "Defense is being implemented"<<endl;
            };
        }
        else{
            currentAction.target = target;
            currentAction.action = [this, target](){//hacemos lo mismo que en player le pasamos el this el target para que pueda atacar
                doAttack(target);
            };
        }

    }
    else{
        currentAction.target = target;
        currentAction.action = [this, target](){//hacemos lo mismo que en player le pasamos el this el target para que pueda atacar
            doAttack(target);
        };
    }

    return currentAction;
}