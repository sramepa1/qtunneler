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

#ifndef _PROJECTILE_H
#define	_PROJECTILE_H

#include "DefaultValues.h"
#include "OrientedRoundObj.h"

class Projectile : public OrientedRoundObj{
public:
    Projectile(qint32 _x, qint32 _y, quint8 _color, qint32 _id, direction _rotation, qint32 _tankID = NO_PLAYER) : OrientedRoundObj(_x, _y, PROJECTILE_RADIUS, _color, _id, _rotation), tankID(_tankID) {}
    //Projectile(const Projectile& orig) : OrientedRoundObj(orig) {} // implicit

    virtual ~Projectile() {}

    qint32 tankID;

};

#endif	/* _PROJECTILE_H */

