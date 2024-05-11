//
// Created by Victor Navarro on 19/02/24.
//

#include "Combat.h"
#include <string>
#include <iostream>
#include <utility>

using namespace std;

bool compareSpeed(Character *a, Character *b) {//esto es para comparar velocidad de los participantes
    return a->getSpeed() > b->getSpeed();//si a es mayor que b retorna true
    //lo esta ordenando del mas chico al mas grande dentro del mismo vector
}

Combat::Combat(vector<Character *> _participants) {/*para separar en dos vectores los jugadores de los enemigos
    ya que ambos estan en el vector de participantes*/
    participants = std::move(_participants);
    for (auto participant: participants) {
        if (participant->getIsPlayer()) {//si el participante es jugador
            partyMembers.push_back((Player *) participant);//se agrega al vector de jugadores
        } else {//di no es jugador
            enemies.push_back((Enemy *) participant);//se agrega a la lista de enemigos
        }
    }
}

Combat::Combat(vector<Player *> _partyMembers, vector<Enemy *> _enemies) {//para implementar los vectores de jugadores y enemigos
    partyMembers = std::move(_partyMembers);//mueve el valor de otra funciom, la esta llamando
    enemies = std::move(_enemies);//mueve el valor de otra funciom, la esta llamando
    participants = vector<Character *>();//inicializamos el vector
    participants.insert(participants.end(), partyMembers.begin(), partyMembers.end());//agregar los partymembers
    participants.insert(participants.end(), enemies.begin(), enemies.end());//agregar enemigod
}

Combat::Combat() {
    participants = vector<Character *>();
}

void Combat::addParticipant(Character *participant) {//para agregar un participante
    participants.push_back(participant);
    if (participant->getIsPlayer()) {//si es un jugador
        partyMembers.push_back((Player *) participant);//se agrega al vector de jugadores
    } else {//si no
        enemies.push_back((Enemy *) participant);//al vector de enemigos
    }
}

void Combat::combatPrep() {
    // Sort participants by speed
    sort(participants.begin(), participants.end(), compareSpeed);
}

string Combat::toString() {
    string result = "";//estamos creando el resultado
    vector<Character *>::iterator it;//estamos declarando un iterador para que se mueva a traves del vector
    /*estamos espacificando que es de tipo vector de tipo character*/
    for (it = participants.begin(); it != participants.end(); it++) {
        /*iterador es igual al primer elemento del vector y lo va a ir recorriendo hasta que el vector se termine*/
        result += (*it)->toString() + "\n";//esto lo que hace es convertir el character a tostring
    }
    cout << "====================" << endl;
    return result;
}

Character *Combat::getTarget(Character *attacker) {//va a retornar un puntero a caracter y va a recibir un atacante
    vector<Character *>::iterator it;//se inicia el iterador para recorrer el vector
    for (it = participants.begin(); it != participants.end(); it++) {
        if ((*it)->getIsPlayer() != attacker->getIsPlayer()) {
            return *it;
        }
        /*lo que hace es que si el getIsplayer es diferente al iterador retorna ese,
         * si soy jugador evaluo si es diferente a mi*/
    }
    //TODO: Handle this exception
    return nullptr;
}

void Combat::doCombat() {
    cout << "Inicio del combate" << endl;
    combatPrep();//ordenar por velocidad a los participantes
    int round = 1;
    //Este while representa las rondas del combate
    while (enemies.size() > 0 && partyMembers.size() > 0) {//si la lista de enemeigos y la lista de participsantes no est vacia
        cout << "Round " << round << endl;
        vector<Character *>::iterator it = participants.begin();
        registerActions(it);
        executeActions(it);

        round++;//se aumenta el numero de ronda
    }

    if (enemies.empty()) {//si ya no hay enemigos, esta vacia la lista
        cout << "You win!" << endl;
    } else {
        cout << "You lose!" << endl;

    }
}

void Combat::executeActions(vector<Character *>::iterator participant) {
    while (!actionQueue.empty()) {//si mi linae de acciones no esta vacia
        Action currentAction = actionQueue.top();//va a sacar la accion
        currentAction.action();//ejecutarla
        actionQueue.pop();//y eliminarla

        //Check if there are any dead characters
        checkParticipantStatus(*participant);
        if (currentAction.target != nullptr)
            checkParticipantStatus(currentAction.target);
    }
}

void Combat::checkParticipantStatus(Character *participant) {//checar el estado de los participantes
    if (participant->getHealth() <= 0) {//si la salud ya es cero o menor

        if (participant->getIsPlayer()) {//si es jugador se elimina de la lista de jugadores
            partyMembers.erase(remove(partyMembers.begin(), partyMembers.end(), participant), partyMembers.end());
        } else {//si es enemigo se elimina de la lista de enemigos
            enemies.erase(remove(enemies.begin(), enemies.end(), participant), enemies.end());
        }
        participants.erase(remove(participants.begin(), participants.end(), participant), participants.end());
    }
}

void Combat::registerActions(vector<Character *>::iterator participantIterator) {
    //Este while representa el turno de cada participante
    //La eleccion que cada personaje elije en su turno
    while (participantIterator != participants.end()) {
        //cout<<"\nregister action: calling take action" ;
        if ((*participantIterator)->getIsPlayer()) {
            //cout<<"\nregister action: player" ;
            Action playerAction = ((Player *) *participantIterator)->takeAction(enemies);//creo una acciom
            actionQueue.push(playerAction);//registramos las acciones en el actionQueue
        } else {
            //cout<<"\nregister action: enemy" ;
            Action enemyAction = ((Enemy *) *participantIterator)->takeAction(partyMembers);
            actionQueue.push(enemyAction);
        }

        participantIterator++;
    }
}