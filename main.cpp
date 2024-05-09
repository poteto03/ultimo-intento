#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"


int main() {
    Player *player = new Player("Victor", 40,40, 3, 4, 3);
    Enemy *enemy = new Enemy("Goblin", 7,15, 6, 2, 5, 10);
    Enemy *enemy2 = new Enemy("Orc", 7,15, 6, 2, 5, 10);

    vector<Character*> participants;

    participants.push_back(player);//agregamos el jugador a participantes
    participants.push_back(enemy);//agregamos al primer enemigo
    participants.push_back(enemy2);//agregamos al segundo enemigo

    Combat *combat = new Combat(participants);
    combat->doCombat();//que se ejecute el combate

    delete player;
    delete enemy;
    delete combat;
    return 0;
}