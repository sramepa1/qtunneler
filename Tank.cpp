/*
 *      -----------------------------------------------
 *      QTunneler - a classic DOS game remake in QT
 *      -----------------------------------------------
 *
 *      semestral project for API programming course
 *      (Y36API) at the FEE CTU Prague
 *
 *      Created by:
 *           Pavel Sramek (sramepa1@fel.cvut.cz)
 *           Martin Smarda (smardmar@fel.cvut.cz)
 *
 *      March & April 2010
 *
 *      This is free software, licensed under GNU LGPL
 *      (GNU Lesser General Public License, version 3)
 *      http://www.gnu.org/licenses/lgpl.html
 *
 *      Project homepage:
 *      http://code.google.com/p/qtunneler/
 *
 *      Version 1.0
 *
 */

#include "Tank.h"

/**
 * Constructs tank and set it's given and default values set in @see DefaultValues.h
 *
 * @param x
 * @param y
 * @param color
 * @param id
 */
Tank::Tank(qint32 x, qint32 y, quint8 color, qint32 id) : OrientedRoundObj(x, y, TANK_RADIUS, color, id, DEFAULT_TANK_ROTATION) {
    hp = DEFAULT_TANK_HP;
    energy = DEFAULT_TANK_ENERGY;
    roundsWon = 0;
    isMoving =  isShoting = turned = false;
    lastRotation = DEFAULT_TANK_ROTATION;
}

/**
 * Constructs a new projectile in front of the tank.
 *
 * @param projectileID
 * @return pointer to the new projectile
 */
Projectile * Tank::fire(quint32 projectileID){
    QPair<qint32, qint32> pair = getMoveCoorinates(radius);

    energy -= TANK_ENERGY_COST_OF_FIRE;

    return new Projectile(pair.first, pair.second, color, projectileID, rotation, id);
}
