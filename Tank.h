/* 
 * File:   Tank.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:39
 */


#ifndef _TANK_H
#define	_TANK_H

#include "RoundObj.h"
#include "DefaultValues.h"

class Tank : public RoundObj {
public:
    Tank(quint32 x, quint32 y, quint8 color, quint32 id) : RoundObj(x, y, color, id) {
        rotation = DEFAULT_TANK_ROTATION;
        hp = DEFAULT_TANK_HP;
        energy =DEFAULT_TANK_ENERGY;
    }
    
    virtual ~Tank();

    direction rotation;
    quint32 hp;
    quint32 energy;
    
private:
    Tank(const Tank& orig) : RoundObj(orig) {} // disabled
};

#endif	/* _TANK_H */

