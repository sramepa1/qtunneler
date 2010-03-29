/* 
 * File:   Base.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:38
 */

#include <qt4/QtCore/qglobal.h>

#include "Base.h"
#include <cmath>

qreal Base::getCircleOverlap(quint32 _x, quint32 _y, quint32 _radius) const {
    //Cokoli jiného má mouchy

    qreal value;

    if((x1 <= _x && x2 >= _x) && (y1 <= _y && y2 >= _y)){
        value = 1;
    }else{
        value = 0;
    }

    return value;
}
