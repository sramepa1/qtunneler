/* 
 * File:   Tank.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:39
 */

#include "Tank.h"

Projectile * Tank::fire(quint32 projectileID){
    QPair<qint32, qint32> pair = getMoveCoorinates(radius);

    energy -= TANK_ENERGY_COST_OF_FIRE;

    return new Projectile(pair.first, pair.second, color, projectileID, rotation);
}
