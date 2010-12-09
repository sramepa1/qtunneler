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

#include "Border.h"

/**
 * Construct the border with dimensions set in @see DefaultValues.h
 */
Border::Border() {
    x1 = BORDER_SIZE;
    y1 = BORDER_SIZE;
    x2 = MATRIX_DIMENSION - BORDER_SIZE;
    y2 = MATRIX_DIMENSION - BORDER_SIZE;
}

/**
 * Returns logical value whether the given point colides with border.
 *
 * @param _x
 * @param _y
 * @return
 */
bool Border::isBorderCollision(qint32 _x, qint32 _y) const{
    if((x1 <= _x && x2 >= _x) && (y1 <= _y && y2 >= _y)){
        return false;
    }

    return true;
}

/**
 * Return logical value whether the given round object colides with border.
 *
 * @param obj
 * @return
 */
bool Border::isBorderCollision(const RoundObj * obj) const{
    qint32 r = obj->getRadius();

    if(((x1 + r) <= obj->getX() && (x2 - r) >= obj->getX()) && ((y1 + r) <= obj->getY() && (y2 - r) >= obj->getY())){
        return false;
    }

    return true;
}


