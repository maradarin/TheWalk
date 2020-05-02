#ifndef _ROBOT_H_
#define _ROBOT_H_
#include <iostream>
using namespace std;

class strategy;
class harta;
class robot //clasa abstracta
    {
private:
    int row, col, viz;
    static int vieti, countItems1, countItems2, countItems3;

public:
    robot();
    pair<int, int> getPos() const; //getter pt pozitia robotului
    void setPos(int, int);
    int getIT(const int) const;
    void setIT(int, int);
    void setViz(int);
    void setVieti(int);
    void stats();
    int getVieti() const;
    int getViz() const;
    static bool correct(const char*, const char); //verifica apartenenta unei litere la un array de caractere
    //metoda este declarata statica pt a putea fi apelata in alta
    //clasa, fara sa declaram un obiect de tip robot
    bool isBlocked(const int, const int, harta&) const; //functie care verifica daca un robot a ramas blocat pe harta
    virtual void Move(harta&, strategy&) = 0; //metoda virtual pura de deplasare a robotuluii
    virtual void EffectItem(const int, const int, harta&) = 0; //metoda virtual pura de folosire a itemului
    virtual ~robot(){};
};

#endif //_ROBOT_H_
