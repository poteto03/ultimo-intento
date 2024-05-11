#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"
#include "Files/FileHandler.h"

Player* loadPlayerInfo() {
    try {
        char buffer[Player::BUFFER_SIZE];
        FileHandler fileHandler = FileHandler();
        fileHandler.readFromFile("PlayerInfo.data", buffer, Player::BUFFER_SIZE);
        return Player::unserialize(buffer);
    } catch(int error) {
        //Preguntar al usuario el nombre de jugador
        return new Player("Victor", 40, 3, 4, 3);
    }
}


int main() {
    Player *player = loadPlayerInfo();
    cout << player->getName() << endl;
    cout << player->toString() << endl;
    Enemy *enemy = new Enemy("Goblin", 15, 6, 2, 5, 10);
    Enemy *enemy2 = new Enemy("Orc", 15, 6, 2, 5, 10);

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