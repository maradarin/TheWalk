#ifndef _JOKER_H_
#define _JOKER_H_

#include "robot.h"

class joker : public robot
{
    int leftCol=0,upRow=0,rightCol=0,downRow=0,mode=0;
public:
    void Move(harta&);
    void EffectItem(int, int, harta&);
    //virtual ~joker();
};

#endif //_JOKER_H_

