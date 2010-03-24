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
    Explosion(int i, int rad, int seed):RoundObj(i),radius(rad),srand(seed) {}
    virtual ~Explosion();

    virtual int getRadius() const {return radius;}
    virtual int getRandomSeed() const {return srand;}

protected:
    int radius;
    int srand;

private:
    Explosion(const Explosion& orig) {} // disabled
};

#endif	/* _EXPLOSION_H */

