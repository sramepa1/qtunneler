/* 
 * File:   Tank.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:39
 */

#include "Tank.h"

Projectile Tank::fire(){
    QPair<qint32, qint32> pair = getMoveCoorinates(radius + PROJECTILE_RADIUS);

    energy -= TANK_ENERGY_COST_OF_FIRE;

    return Projectile(pair.first, pair.second, color, 111111, rotation); //TODO system for IDs
}
