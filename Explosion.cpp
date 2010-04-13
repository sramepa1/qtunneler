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

#include "Explosion.h"
#include "BitmapObj.h"

BitmapObj Explosion::getExplosionMask() {

    BitmapObj mask(x1, y1, 2 * radius, 2 * radius);
    qsrand(seed);
    qreal chance;
    qreal distance;

    for (int i = x1; i < x2; i++) {
        for (int j = y1; j < y2; j++) {

            //if is in circle
            if(isWithinCircle(i, j)){
                chance = ((qreal) qrand() / RAND_MAX);
                distance = (qreal) getDistanceFormCenter(i, j) / radius;

                if(distance > EXPLOSION_RAND_SOLID_PART){
                    if(chance >= (distance - EXPLOSION_RAND_SOLID_PART) * 2){
                        mask.setXYGlobalCoordiantes(i, j, true);
                    }else{
                        mask.setXYGlobalCoordiantes(i, j, false);
                    }
                }else{
                    mask.setXYGlobalCoordiantes(i, j, true);
                }

            }else{
                mask.setXYGlobalCoordiantes(i, j, false);
            }
        }
    }

    return mask;
}

qint32 Explosion::countDamageToObj(const RoundObj * obj, qint32 maxDamage){
    //No damage from own shots explosions
    if(obj->color == color){
        return 0;
    }

    //Distance of round obj border from explosion center
    qreal distance = getDistanceFormCenter(obj->getX(), obj->getY()) - obj->getRadius();

    if(0 > distance){
        distance = 0;
    }

    return (qint32)( (1 - (distance/radius)) * maxDamage);
}
