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
    Projectile(quint8 c, quint8 rot):rotation(rot),RoundObj(c) {}
    virtual ~Projectile();

    virtual quint8 getRotation() const {return rotation;}

protected:
    quint8 rotation;

private:
    Projectile(const Projectile& orig) {} // disabled
};

#endif	/* _PROJECTILE_H */

