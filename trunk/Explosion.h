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
    Explosion(quint8 c, quint32 rad, qint32 seed):RoundObj(c),radius(rad),srand(seed) {}
    virtual ~Explosion();

    virtual quint32 getRadius() const {return radius;}
    virtual qint32 getRandomSeed() const {return srand;}

protected:
    quint32 radius;
    qint32 srand;

private:
    Explosion(const Explosion& orig) {} // disabled
};

#endif	/* _EXPLOSION_H */

