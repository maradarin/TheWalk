#ifndef _BATMAN_H_
#define _BATMAN_H_

#include "robot.h"

class batman : public robot
{
public:
    void Move(harta&);                          //Robot1 se deplaseaza pe coloane
    void EffectItem(int, int, harta&);
    //virtual ~batman();
};


#endif //_BATMAN_H_

