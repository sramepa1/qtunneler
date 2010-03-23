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
    Tank(int i):RoundObj(i) {}
    virtual ~Tank();

    char rotation;
    int hp;
    int energy;
    
private:

    Tank(const Tank& orig);
};

#endif	/* _TANK_H */

