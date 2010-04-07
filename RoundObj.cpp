/* 
 * File:   RoundObj.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:38
 */

#include "RoundObj.h"


bool RoundObj::isWithinCircle(quint32 _x, quint32 _y) {
    return ((x - _x) * (x - _x) + (y - _y) * (y - _y)) <= (radius * radius);
}

quint32 RoundObj::getDistanceFormCenter(quint32 _x, quint32 _y) {
    return (quint32) sqrt((x - _x) * (x - _x) + (y - _y) * (y - _y));
}