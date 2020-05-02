#ifndef _BATMAN_H_
#define _BATMAN_H_

#include "robot.h"

class batman : public robot {
public:
    void Move(harta&, strategy&); //Robot1 vrea sa ajunga neaparat la destinatie, cu pierderi minime
    void EffectItem(const int, const int, harta&);
    virtual ~batman(){};
};

#endif //_BATMAN_H_
