
#ifndef _ROBOT_H_
#define _ROBOT_H_
#include <iostream>
using namespace std;


class harta;
class robot                                                 //clasa abstracta
{
protected:
    int row,col,viz;
    int vieti,countItems1,countItems2,countItems3;
public:
    //friend class harta;
    robot():row(0),col(0),vieti(4),countItems1(0),countItems2(0),countItems3(0),viz(2) {}
    int getRow() {return row;}
    int getCol() {return col;}
    int getVieti() {return vieti;}
    int getViz() {return viz;}
    int getItems1() {return countItems1;}
    int getItems2() {return countItems2;}
    int getItems3() {return countItems3;}
    virtual void Move(harta&)=0;             //metoda virtual pura de deplasare a robotuluii
    virtual void EffectItem(int, int, harta&)=0;     //metoda virtual pura de folosire a itemului
    //~robot();
};

//int robot::numberLives=4;

#endif //_ROBOT_H_
