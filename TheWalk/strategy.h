#ifndef _STRATEGY_H_
#define _STRATEGY_H_
#include <iostream>
#include <vector>
#include "harta.h"
using namespace std;

class harta;
class joker;
class strategy {
    int n, m;
    int** dist;
    vector<pair<int, int> > ZCoord; //vector de coordonate ale senzorilor
public:
    strategy(int, int);
    bool isValid(const int, const int, const char, char**) const; //verifica daca o celula apartine hartii
    bool findCoord(int, int, vector<pair<int, int> >) const; //verifica prezenta unei perechi de coordonate intr-o coada;
    //metoda folosita pt marcarea senzorilor
    bool isBlocked(const int, const int, harta&) const; //metoda aditionala la cea din robot; folosita doar pt robin
    bool threeCells(int&, int&, harta&, const char*, joker&) const;
    void trigger(const int, const int, const int, char**); //marcheaza prezenta senzorilor in perimetrul vizibil
    void check(pair<int, int> curr, int viz, char**); //marcheaza la fiecare runda casutele in care se poate muta robotul
    int getCell(const int, const int) const; //getter pt matricea de distante
    ~strategy();
};

#endif //_STRATEGY_H_
