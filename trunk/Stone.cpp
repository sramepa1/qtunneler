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

#include "Stone.h"

Stone::Stone(qint32 _x, qint32 _y, qint32 _width, qint32 _height) : BitmapObj(_x, _y, _width, _height) {
    color = QColor("darkGray");

    Q_ASSERT(_width % 8 == 0);

    for(qint32 i = 0; i < _width/8; i++){
        for (qint32 j = 0; j < _height; j++) {
            setByte(i, j, 0xFF);
        }
    }
}

