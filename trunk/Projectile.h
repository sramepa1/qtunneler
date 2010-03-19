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
    Projectile();
    Projectile(const Projectile& orig);
    virtual ~Projectile();
private:

};

#endif	/* _PROJECTILE_H */

