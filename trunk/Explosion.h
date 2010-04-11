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
    Explosion(qint32 x, qint32 y, quint8 color, qint32 _seed, qint32 radius = EXPLOSION_RADIUS,qint32 _increase = EXPLOSION_RAND_INCREASE) : RoundObj(x,y,radius,color), seed(_seed), increase(_increase) {}
    //Explosion(const Explosion& orig) : RoundObj(orig) {} // implicit
    virtual ~Explosion() {}

    /**
     * Get bitmap mask exposion to burn clay in matrix. 1 = unchanged, 0 = tunnel
     */
    virtual BitmapObj getExplosionMask();

    qint32 countDamageToObj(RoundObj * obj);

    qint32 seed;
    qint32 increase;
};

#endif	/* _EXPLOSION_H */

