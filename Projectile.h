/* 
 * File:   Projectile.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:41
 */

#ifndef _PROJECTILE_H
#define	_PROJECTILE_H

#include "DefaultValues.h"
#include "OrientedRoundObj.h"

class Projectile : public OrientedRoundObj{
public:
    Projectile(qint32 _x, qint32 _y, quint8 _color, qint32 _id, direction _rotation) : OrientedRoundObj(_x, _y, PROJECTILE_RADIUS, _color, _id, _rotation) {}
    //Projectile(const Projectile& orig) : OrientedRoundObj(orig) {} // implicit

    virtual ~Projectile();

    
};

#endif	/* _PROJECTILE_H */

