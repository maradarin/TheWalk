#ifndef _GAME_H_
#define _GAME_H_

#include "harta.h"
#include "strategy.h"
#include "robot.h"

class game //singleton
    {
    harta* plan;
    robot* pawn;
    static game* route; //unica instanta

    game(); //constructorul privat nu permite instantierea
    ~game();

public:
    void play();
    void setRobot1();
    void setRobot2();
    void setRobot3();
    static game* instance() //aceasta metoda statica e folosita pt accesarea
    //singurei instante
    {
        return route;
    }
};

#endif //_GAME_H_
