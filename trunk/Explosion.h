/* 
 * File:   Explosion.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:38
 */

#ifndef _EXPLOSION_H
#define	_EXPLOSION_H

#include "RoundObj.h"
#include "DefaultValues.h"

class Explosion : public RoundObj{
public:
    Explosion(quint32 x, quint32 y, quint8 color, quint32 id, quint32 _radius, qint32 _seed) : RoundObj(x,y,color,id), radius(_radius), seed(_seed) {}
    virtual ~Explosion();

    virtual quint32 getRadius() const {return radius;}
    virtual qint32 getRandomSeed() const {return seed;}

protected:
    quint32 radius;
    qint32 seed;

private:
    Explosion(const Explosion& orig) : RoundObj(orig) {} // disabled
};

#endif	/* _EXPLOSION_H */

