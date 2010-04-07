/* 
 * File:   Explosion.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:38
 */

#include "Explosion.h"
#include "BitmapObj.h"

BitmapObj Explosion::getExplosionMask() {
    quint32 mx = x - radius;
    quint32 my = y - radius;
    quint32 mwidth = 2 * radius;
    quint32 mheight = 2 * radius;

    BitmapObj mask(mx, my, mwidth, mheight);

    for (int i = 0; i < mwidth; i++) {
        for (int j = 0; j < mheight; j++) {
            //if is in circle
            if(isWithinCircle(i, j)){
                mask.setXY(i, j, false); //TODO use random seed
            }else{
                mask.setXY(i, j,true);
            }
        }
    }

    return mask;
}

