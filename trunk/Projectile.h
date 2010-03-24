/* 
 * File:   Projectile.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:41
 */

#ifndef _PROJECTILE_H
#define	_PROJECTILE_H

#include "RoundObj.h"

class Projectile : public RoundObj{
public:
    Projectile(int i, char rot):rotation(rot),RoundObj(i) {}
    virtual ~Projectile();

    virtual char getRotation() const {return rotation;}

protected:
    char rotation;

private:
    Projectile(const Projectile& orig) {} // disabled
};

#endif	/* _PROJECTILE_H */

