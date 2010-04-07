/* 
 * File:   Explosion.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:38
 */

#ifndef _EXPLOSION_H
#define	_EXPLOSION_H

#include "RoundObj.h"
#include "BitmapObj.h"
#include "DefaultValues.h"

class Explosion : public RoundObj{
public:
    Explosion(quint32 x, quint32 y, quint8 color, quint32 id, qint32 _seed, quint32 radius = EXPLOSION_RADIUS) : RoundObj(x,y,radius,color,id), seed(_seed) {}
    virtual ~Explosion() {}

    /**
     * Get bitmap mask exposion to burn clay in matrix. 1 = unchanged, 0 = tunnel
     */
    virtual BitmapObj getExplosionMask();

    qint32 seed;

private:
    Explosion(const Explosion& orig) : RoundObj(orig) {} // disabled
};

#endif	/* _EXPLOSION_H */

