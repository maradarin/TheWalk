#ifndef _ROBIN_H_
#define _ROBIN_H_

#include "robot.h"
#include <vector>

class robin : public robot
{
    vector<pair<int,int> > Coord2;
public:
    void Move(harta&);                         //Robot2 se deplaseaza pe coloane
    void EffectItem(int, int, harta&);
    bool findCoord(int, int);
    //virtual ~robin();
};

#endif //_ROBIN_H_

