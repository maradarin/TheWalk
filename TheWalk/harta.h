#ifndef _HARTA_H
#define _HARTA_H
#include <fstream>
#include <vector>
#include "strategy.h"
using namespace std;
class robot;
class strategy;
class harta
{
private:
    int n,m;                                    //dimensiunile matricei
    char **matrix;                              //harta pe care se deplaseaza Robotul
    pair<int,int>finish;                        //destinatia Robotului
    int numberItems,numberBombs,numberSensors;
    robot *A;                                   //pointer catre un obiect de tip robot
    strategy *S;                                //pointer catre un obiect de tip strategy
    static int numberRound;                     //numarul de runde pe care le-a avut Robotul
public:
    friend class batman;
    friend class robin;
    friend class joker;
    harta(int, int);                            //constructor cu parametri default
    ~harta();                                   //destructor
    char getCell(const int, const int) const;   //getter care returneaza valoarea dintr-o celula a hartii
    pair<int, int> getDim() const;              //getter pt dimensiunile hartii, returnate sub forma de pereche
    friend ostream & operator << (ostream &, const harta &);
    void Simulate(robot &A);                    //metoda prin care simulam desfasurarea jocului
};

#endif // MAP_H

