/* 
 * File:   Tank.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:39
 */


#ifndef _TANK_H
#define	_TANK_H

/* Round object's directions
 *
 *         7  0  1
 *          \ | /
 *        6 - + - 2
 *          / | \
 *         5  4  3
 */

enum directions {
    NORTH, NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST
};


#include "RoundObj.h"

class Tank : public RoundObj {
public:
    Tank(quint32 x, quint32 y, quint8 color, quint32 id) : RoundObj(x, y, color, id) {} //TODO load default values
    virtual ~Tank();

    directions rotation;
    quint32 hp;
    quint32 energy;
    
private:
    Tank(const Tank& orig) : RoundObj(orig) {} // disabled
};

#endif	/* _TANK_H */

