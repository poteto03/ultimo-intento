//
// Created by Victor Navarro on 19/02/24.
//

#ifndef RPG_COMBAT_H
#define RPG_COMBAT_H
#include <vector>
#include "../Character/Character.h"
#include "../Player/Player.h"
#include "../Enemy/Enemy.h"
#include <queue>//incluimos la prioridad de las acciones

class Combat {
private:
    vector<Character*> participants;//vector que contiene la lista de participantes
    vector<Player*> partyMembers;//vector que contiene la lista de jugadores
    vector<Enemy*> enemies;//vector que contiene la lista de enemigos
    priority_queue<Action> actionQueue;//agregamos la prioridad de las acciones al actionQueue,va a ser tipo accion
    void registerActions(vector<Character*>::iterator participant);//metodo para registrar las acciones, recibe un puntero a un participant
    void executeActions(vector<Character*>::iterator participant);//metodo para ejecutar las acciones
    void checkParticipantStatus(Character* participant);

    void combatPrep();
    Character* getTarget(Character* attacker);//or
    //para definir quien es atacado
public:
    Combat(vector<Character*> _participants);
    Combat(vector<Player*> _partyMembers, vector<Enemy*> _enemies);//constructor que recibe vector de jugadores y vewctor de enemigos
    Combat();
    void doCombat();
    void addParticipant(Character *participant);//funcion para agrgar un participante, agrega un elemento al vector al final
    string toString();
};


#endif //RPG_COMBAT_H
