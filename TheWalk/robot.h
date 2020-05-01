#ifndef _ROBOT_H_
#define _ROBOT_H_
#include <iostream>
using namespace std;


class harta;
class robot                                                 //clasa abstracta
{
private:
    int row,col,viz;
    static int vieti,countItems1,countItems2,countItems3;
public:
    robot():row(0),col(0),viz(2) {}
    pair<int,int> getPos() const;                                  //getter pt pozitia robotului
    void setPos(int, int);
    int getVieti() const {return vieti;}
    int getViz() const {return viz;}
    int getIT(int) const;
    void setIT(int, int);
    void setLife(int);
    void setViz(int);
    bool isBlocked(const int, const int, harta&) const;            //functie care verifica daca un robot a ramas blocat pe harta
    void stats();
    virtual void Move(harta&)=0;                                   //metoda virtual pura de deplasare a robotuluii
    virtual void EffectItem(const int, const int, harta&)=0;       //metoda virtual pura de folosire a itemului
    virtual ~robot() {};
};

//int robot::numberLives=4;

#endif //_ROBOT_H_
