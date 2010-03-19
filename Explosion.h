/* 
 * File:   Explosion.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:38
 */

#ifndef _EXPLOSION_H
#define	_EXPLOSION_H

#include "RoundObj.h"

class Explosion : public RoundObj{
public:
    Explosion();
    Explosion(const Explosion& orig);
    virtual ~Explosion();
private:

};

#endif	/* _EXPLOSION_H */

