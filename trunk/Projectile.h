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
    Projectile(quint32 x, quint32 y, quint8 color, quint32 id, direction rotation) : OrientedRoundObj(x, y, color, id, rotation) {}
    virtual ~Projectile();

private:
    Projectile(const Projectile& orig) : OrientedRoundObj(orig) {} // disabled
};

#endif	/* _PROJECTILE_H */
