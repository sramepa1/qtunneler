/* 
 * File:   Tank.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:39
 */

#include "Tank.h"

Tank::Tank(qint32 x, qint32 y, quint8 color, qint32 id) : OrientedRoundObj(x, y, TANK_RADIUS, color, id, DEFAULT_TANK_ROTATION) {
    hp = DEFAULT_TANK_HP;
    energy = DEFAULT_TANK_ENERGY;
    roundsWon = 0;
    isMoving =  isShoting = turned = false;
}

Projectile * Tank::fire(quint32 projectileID){
    QPair<qint32, qint32> pair = getMoveCoorinates(radius);

    energy -= TANK_ENERGY_COST_OF_FIRE;

    return new Projectile(pair.first, pair.second, color, projectileID, rotation, id);
}