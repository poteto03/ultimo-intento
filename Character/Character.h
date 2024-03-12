//
// Created by Victor Navarro on 15/02/24.
//

#ifndef RPG_CHARACTER_H
#define RPG_CHARACTER_H
#include <string>

using namespace std;

class Character {
protected:
    string name;
    int health;
    int attack;
    int defense;
    int speed;
    bool isPlayer;//para definir si el participante es jugador o enemigo
public:
    Character(string _name, int _health, int _attack, int _defense, int _speed, bool _isPlayer);

    virtual void doAttack(Character *target) = 0;
    virtual void takeDamage(int damage) = 0;

    //TODO: Implementar metodo de defensa
    //Incrementar la defensa un 20% solo por el turno actual
    void defend();

    bool flee(Character* target);//para que el participante escape. Recibe al enemigo del que se quiere escapar
    string getName();
    int getHealth();
    int getAttack();
    int getDefense();
    bool getIsPlayer();//para definir si el participante es jugador o enemigo
    int getSpeed();
    string toString();
};
#endif //RPG_CHARACTER_H
