
#ifndef _STRATEGY_H_
#define _STRATEGY_H_
#include <iostream>
#include <vector>
using namespace std;

class strategy
{
    int n,m;
    int **dist;
    vector<pair<int,int> > ZCoord;                                  //vector de coordonate ale senzorilor
public:
    strategy(int, int);
    bool isValid(const int, const int, const char, char **) const;  //verifica daca o celula apartine hartii
    bool findCoord(int, int) const;                                 //verifica prezenta unei perechi de coordonate intr-o coada
                                                                    //metoda folosita pt marcarea senzorilor
    void trigger(const int, const int, const int, char **);         //verifica prezenta senzorilor in perimetrul vizibil
    void check(pair<int,int> curr, int viz, char **);               //functie ce marcheaza la fiecare mutare casutele in care se poate muta robotul
    int getCell(const int, const int) const;                        //getter pt matricea de distante
    ~strategy();
};

#endif //_STRATEGY_H_

