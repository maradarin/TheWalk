#ifndef _ROBOT_H_
#define _ROBOT_H_
#include <iostream>
using namespace std;


class harta;
class robot                                                 //clasa abstracta
{
protected:
    int row,col,viz;
    static int vieti,countItems1,countItems2,countItems3;
public:
    //friend class harta;
    robot():row(0),col(0),viz(2) {}
    int getRow() {return row;}
    int getCol() {return col;}
    int getVieti() {return vieti;}

    bool isBlocked(int, int, harta&);                //functie care verifica daca un robot a ramas blocat pe harta
    void stats();
    virtual void Move(harta&)=0;                     //metoda virtual pura de deplasare a robotuluii
    virtual void EffectItem(int, int, harta&)=0;     //metoda virtual pura de folosire a itemului
    //~robot();
};

//int robot::numberLives=4;

#endif //_ROBOT_H_
