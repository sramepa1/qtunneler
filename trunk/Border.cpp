/* 
 * File:   Border.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:36
 */

#include "Border.h"

Border::Border() {
    x1 = BORDER_SIZE;
    y1 = BORDER_SIZE;
    x2 = MATRIX_DIMENSION - BORDER_SIZE;
    y2 = MATRIX_DIMENSION - BORDER_SIZE;
}

bool Border::isBorderCollision(qint32 _x, qint32 _y) const{
    if((x1 <= _x && x2 >= _x) && (y1 <= _y && y2 >= _y)){
        return false;
    }

    return true;
}

bool Border::isBorderCollision(const RoundObj * obj) const{
    qint32 r = obj->getRadius();

    if(((x1 + r) <= obj->getX() && (x2 - r) >= obj->getX()) && ((y1 + r) <= obj->getY() && (y2 - r) >= obj->getY())){
        return false;
    }

    return true;
}


