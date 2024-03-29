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

#include "Base.h"

/**
 * Checks if the given point is within base.
 *
 * @param _x x-axes coordinates of point
 * @param _y x-axes coordinates of point
 * @return logic value if the given point is in base
 */
bool Base::isWithinBase(qint32 _x, qint32 _y) const{
    if((x1 <= _x && x2 >= _x) && (y1 <= _y && y2 >= _y)){
        return true;
    }

    return false;
}
