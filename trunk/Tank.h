/* 
 * File:   Tank.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:39
 */


#ifndef _TANK_H
#define	_TANK_H

#include "DefaultValues.h"
#include "OrientedRoundObj.h"
#include "Projectile.h"

class Tank : public OrientedRoundObj {
public:
    Tank(qint32 x, qint32 y, quint8 color, qint32 id) : OrientedRoundObj(x, y, TANK_RADIUS, color, id, DEFAULT_TANK_ROTATION) {
        hp = DEFAULT_TANK_HP;
        energy = DEFAULT_TANK_ENERGY;
        isMoving = false;
    }
    virtual ~Tank(){}

    virtual Projectile fire();
    virtual void move(qint32 steps = 1);
    virtual void moveInClue(qint32 steps = 1);

    qint32 hp;
    qint32 energy;
    bool isMoving;

private:
    Tank(const Tank& orig) : OrientedRoundObj(orig) {} // disabled
};

#endif	/* _TANK_H */

