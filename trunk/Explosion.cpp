/* 
 * File:   Explosion.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:38
 */

#include "Explosion.h"
#include "BitmapObj.h"

BitmapObj Explosion::getExplosionMask() {

    BitmapObj mask(x1, y1, 2 * radius, 2 * radius);

    for (int i = x1; i < x2; i++) {
        for (int j = y1; j < y2; j++) {
            //if is in circle
            if(isWithinCircle(i, j)){
                mask.setXYGlobalCoordiantes(i, j, false); //TODO use random seed
            }else{
                mask.setXYGlobalCoordiantes(i, j, true);
            }
        }
    }

    return mask;
}

quint32 Explosion::countDamageToObj(RoundObj * obj){
    //No damage from own shots explosions
    if(obj->color == color){
        return 0;
    }

    //Distance of round obj border from explosion center
    qreal distance = getDistanceFormCenter(obj->getX(), obj->getY()) - obj->getRadius();

    if(0 > distance){
        distance = 0;
    }

    return (quint32)( (1 - (distance/radius)) * EXPLOSION_DAMAGE );
}
