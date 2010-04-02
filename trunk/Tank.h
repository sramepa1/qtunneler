/* 
 * File:   Tank.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:39
 */


#ifndef _TANK_H
#define	_TANK_H

#include "DefaultValues.h"
#include "OrientedRoundObj.h"

class Tank : public OrientedRoundObj {
public:
    Tank(quint32 x, quint32 y, quint8 color, quint32 id) : OrientedRoundObj(x, y, color, id, DEFAULT_TANK_ROTATION) {
        hp = DEFAULT_TANK_HP;
        energy =DEFAULT_TANK_ENERGY;
    }
    
    virtual ~Tank();

    quint32 hp;
    quint32 energy;
    
private:
    Tank(const Tank& orig) : OrientedRoundObj(orig) {} // disabled
};

#endif	/* _TANK_H */

