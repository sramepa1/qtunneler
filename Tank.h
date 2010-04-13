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

#ifndef _TANK_H
#define	_TANK_H

#include "DefaultValues.h"
#include "OrientedRoundObj.h"
#include "Projectile.h"
#include "BitmapObj.h"

class Tank : public OrientedRoundObj {
public:
    Tank(qint32 x, qint32 y, quint8 color, qint32 id);
    virtual ~Tank(){}

    virtual Projectile * fire(quint32 projectileID);

    qint32 hp;
    qint32 energy;

    qint32 roundsWon;

    direction lastRotation;

    bool isMoving;
    bool isShoting;
    bool turned;
};

#endif	/* _TANK_H */

