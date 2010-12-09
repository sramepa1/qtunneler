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

#ifndef _EXPLOSION_H
#define	_EXPLOSION_H

#include "RoundObj.h"
#include "BitmapObj.h"
#include "DefaultValues.h"

/**
 * This class represents explosion, which is descendatnt of @see RoundObj .
 */
class Explosion : public RoundObj{
public:
    Explosion(qint32 _x, qint32 _y, quint8 _color, qint32 _seed, qint32 _radius = EXPLOSION_RADIUS, qint32 _increase = EXPLOSION_RAND_SOLID_PART) : RoundObj(_x,_y,_radius,_color), seed(_seed), increase(_increase) {}
    //Explosion(const Explosion& orig) : RoundObj(orig) {} // implicit
    virtual ~Explosion() {}

    /**
     * Get bitmap mask exposion to burn clay in matrix. 1 = unchanged, 0 = tunnel
     */
    virtual BitmapObj getExplosionMask();

    qint32 countDamageToObj(const RoundObj * obj, qint32 maxDamage = EXPLOSION_DAMAGE);

    qint32 seed;
    qint32 increase;
};

#endif	/* _EXPLOSION_H */

