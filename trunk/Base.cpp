/* 
 * File:   Base.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:38
 */

#include <qt4/QtCore/qglobal.h>

#include "Base.h"

bool Base::isWithinBase(qint32 _x, qint32 _y) const{
    if((x1 <= _x && x2 >= _x) && (y1 <= _y && y2 >= _y)){
        return true;
    }

    return false;
}
