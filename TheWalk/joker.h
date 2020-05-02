#ifndef _JOKER_H_
#define _JOKER_H_

#include "robot.h"

class joker : public robot {
    static int leftCol, upRow, rightCol, downRow, mode;

public:
    void Move(harta&, strategy&); //Un wildcard, daca intalneste capcane pe drum, nu le evita
    void EffectItem(const int, const int, harta&);
    int getLeft() const;
    int getRight() const;
    int getUp() const;
    int getDown() const;
    int getMode() const;
    virtual ~joker(){};
};

#endif //_JOKER_H_
