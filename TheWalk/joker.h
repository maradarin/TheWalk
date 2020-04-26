#ifndef _JOKER_H_
#define _JOKER_H_

#include "robot.h"

class joker : public robot
{
    static int leftCol,upRow,rightCol,downRow,mode;
public:
    void Move(harta&);
    void EffectItem(int, int, harta&);
    //virtual ~joker();
};

#endif //_JOKER_H_

