//
// Created by Victor Navarro on 15/02/24.
//

#include "Player.h"
#include <iostream>
#include "../Files/FileHandler.h"

using namespace std;

void Player::saveProgress() {
    char* buffer = this->serialize();
    FileHandler fileHandler = FileHandler();

    fileHandler.writeToFile("PlayerInfo.data", buffer, Player::BUFFER_SIZE);
}

Player::Player(char* _name, int _health, int _attack, int _defense, int _speed) : Character(_name, _health,_attack,_defense, _speed, true) {
    level = 1;
    experience = 0;
}

Player::Player(char* _name, int _health, int _attack, int _defense, int _speed,bool _isPlayer,bool _isDefending, int _level, int _experience): Character(_name, _health,_attack,_defense, _speed, _isPlayer, _isDefending){
    level=_level;
    experience=_experience;
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
    cout<<name<<" is now in level "<<level<<endl;//ahora subio de nivel

    health+=15;
    attack+=15;
    defense+=15;
    speed+=15;

    cout<<"You have new powers"<<endl;
    cout<<"+10 points health points"<<endl;
    cout<<"+10 points attack points"<<endl;
    cout<<"+10 points defence points"<<endl;
    cout<<"+10 points speed points"<<endl;

}

void Player::gainExperience(int exp) {//cuando el jugador gana 100 de experiencia, sube de nivel
    experience += exp;
    cout << "You won "<< exp << "points of experience"<<endl;
    if (experience >= 100) {
        levelUp();
        experience = 100 - experience;
    }
}

Character *Player::selectTarget(vector<Enemy *> possibleTargets) {
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
         << "2. Defend" << endl//agrego la opcion para que el jugador se pueda defender
         <<" 3. Save the progress"<<endl;//Elegir guardar la partida

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
        case 3:
            saveProgress();
            return takeAction(enemies);
            break;
        default:
            cout << "Invalid action" << endl;
            return takeAction(enemies);
            break;
    }

    return currentAction;
}

char* Player::serialize(){
    char* iterator=buffer;

    memcpy(iterator,&name, sizeof(name));
    iterator += sizeof(name);

    memcpy(iterator,&health, sizeof(health));
    iterator += sizeof(health);

    memcpy(iterator,&attack, sizeof(attack));
    iterator += sizeof(attack);

    memcpy(iterator,&defense, sizeof(defense));
    iterator += sizeof(defense);

    memcpy(iterator,&speed, sizeof(speed));
    iterator += sizeof(speed);

    memcpy(iterator,&isPlayer, sizeof(isPlayer));
    iterator += sizeof(isPlayer);

    memcpy(iterator,&isDefending, sizeof(isDefending));
    iterator += sizeof(isDefending);

    memcpy(iterator,&level, sizeof(level));
    iterator += sizeof(level);

    memcpy(iterator,&experience, sizeof(experience));
    iterator += sizeof(experience);

    return buffer;
};//para serializar

Player* Player::unserialize(char *buffer) {
    char* iterator = buffer;
    char name[30];
    int health,attack,defense,speed,level,experience;
    bool isPlayer,isDefending;

    memcpy(&name,buffer, sizeof(name));
    iterator += sizeof(name);

    memcpy(&health,buffer, sizeof(health));
    iterator += sizeof(health);

    memcpy(&attack,buffer, sizeof(attack));
    iterator += sizeof(attack);

    memcpy(&defense,buffer, sizeof(defense));
    iterator += sizeof(defense);

    memcpy(&speed,buffer, sizeof(speed));
    iterator += sizeof(speed);

    memcpy(&isPlayer,buffer, sizeof(isPlayer));
    iterator += sizeof(isPlayer);

    memcpy(&isDefending,buffer, sizeof(isDefending));
    iterator += sizeof(isDefending);

    memcpy(&level,buffer, sizeof(level));
    iterator += sizeof(level);

    memcpy(&experience,buffer, sizeof(experience));
    iterator += sizeof(experience);

    return new Player(name,health,attack,defense,speed,isPlayer,isDefending,level,experience);

}