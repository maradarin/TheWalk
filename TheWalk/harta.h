
#ifndef _HARTA_H
#define _HARTA_H
#include <fstream>
#include <vector>
using namespace std;
class robot;
class harta
{
private:
    int n,m;                                 //dimensiunile matricei;
    char **matrix;                           //harta pe care se deplaseaza Robotul
    pair<int,int>finish;                     //destinatia Robotului
    int numberItems,numberTraps,numberSensors;
    vector<pair<int,int> > ZCoord;           //vector de coordonate ale senzorilor
    robot *A;                                //pointer catre un obiect de tip robot
    static int numberRound;                  //numarul de runde pe care le-a avut Robotul
public:
    friend class batman;
    friend class robin;
    friend class joker;
    harta();                                 //constructor fara parametri
    ~harta();                                //destructor
    char getCell(int, int);                  // getter care returneaza valoarea dintr-o celula a hartii
    friend istream & operator >> (istream &, harta &);
    friend ostream & operator << (ostream &, const harta &);
    bool isValid(int, int, char);            //verifica daca o celula apartine hartii
    bool findCoord(int, int);                //verifica prezenta unei perechi de coordonate intr-o coada; metoda folosita pt marcarea senzorilor
    void check(pair<int,int>, int, int a[20][20]);   //functie ce marcheaza la fiecare mutare casutele in care se poate muta robotul
    void trigger(int, int, int);             //verifica prezenta senzorilor in perimetrul vizibil
    void Simulate(robot &A);                 //metoda prin care simulam desfasurarea jocului
};

#endif // MAP_H

