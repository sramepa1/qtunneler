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

#include "OrientedRoundObj.h"

/**
 * ¨Returns pair of coordinates of new object's position.
 *
 * @param steps how many pixels shall the object move
 * @return pair of new coordinates
 */
QPair<qint32, qint32> OrientedRoundObj::getMoveCoorinates(qint32 steps){
    qint32 x = this->x;
    qint32 y = this->y;
    qint32 diagonalSteps = (qint32)round(steps * M_SQRT1_2);

    switch (rotation){
        case NORTH :                            y -= steps;         break;
        case NORTH_EAST :   x += diagonalSteps; y -= diagonalSteps; break;
        case EAST :         x += steps;                             break;
        case SOUTH_EAST :   x += diagonalSteps; y += diagonalSteps; break;
        case SOUTH :                            y += steps;         break;
        case SOUTH_WEST :   x -= diagonalSteps; y += diagonalSteps; break;
        case WEST :         x -= steps;                             break;
        case NORTH_WEST :   x -= diagonalSteps; y -= diagonalSteps; break;
    }

    return QPair<qint32, qint32>(x, y);
}

/**
 * Change the objet's position by the given steps.
 *
 * @param steps how many pixels shall the object move
 */
void OrientedRoundObj::move(qint32 steps){
    QPair<qint32, qint32> pair = getMoveCoorinates(steps);
    x = pair.first;
    y = pair.second;

    x1 = x - radius;
    y1 = y - radius;
    x2 = x + radius;
    y2 = y + radius;
}


