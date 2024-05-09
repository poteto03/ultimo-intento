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
    int OgHealth;//Para poder evaluar la salud de mi participante despues, necesito ver cuanto le queda de vida a mi enemigo y tengo que establecer este valor que no va ser alterado al lo largo del cogigo para establecer mi referencia 13/03/24
    int attack;
    int defense;
    int speed;
    bool isPlayer;//para definir si el participante es jugador o enemigo
    bool isDefending;//estoy creando esta variable para de definir un estado booleano de que si me estoy defendiendo
public:
    Character(string _name, int _health, int _OgHealth, int _attack, int _defense, int _speed, bool _isPlayer);

    virtual void doAttack(Character *target) = 0;
    virtual void takeDamage(int damage) = 0;

    //TODO: Implementar metodo de defensa
    //Incrementar la defensa un 20% solo por el turno actual
    void doDefense();//creo mi void de defensa para implemente el estado

    bool flee(Character* target);//para que el participante escape. Recibe al enemigo del que se quiere escapar
    string getName();
    int getHealth();
    int getOgHealth();
    int getAttack();
    double getDefense();//antes era int, camcio a double por el calculo del aumento de la defensa
    bool getIsPlayer();//para definir si el participante es jugador o enemigo
    int getSpeed();
    string toString();
};
#endif //RPG_CHARACTER_H
