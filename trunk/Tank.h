/* 
 * File:   Tank.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:39
 */

#ifndef _TANK_H
#define	_TANK_H

#include "RoundObj.h"

class Tank : public RoundObj {
public:
    Tank(quint32 c):RoundObj(c) {}
    virtual ~Tank();

    quint8 rotation;
    quint32 hp;
    quint32 energy;
    
private:
    Tank(const Tank& orig) {} // disabled
};

#endif	/* _TANK_H */

