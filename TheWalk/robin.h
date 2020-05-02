#ifndef _ROBIN_H_
#define _ROBIN_H_

#include "robot.h"
#include <vector>

class robin : public robot {
    vector<pair<int, int> > Coord2;

public:
    void Move(harta&, strategy&); //Robot2 vrea sa ajunga la destinatie, adunand cat mai multe itemuri 2
    void EffectItem(const int, const int, harta&);
    virtual ~robin();
};

#endif //_ROBIN_H_
