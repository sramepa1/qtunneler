/* 
 * File:   RoundObj.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:38
 */

#include "RoundObj.h"

void RoundObj::setX(qint32 _x) {
    x = _x;

    x1 = x - radius;
    x2 = x + radius;
}
void RoundObj::setY(qint32 _y) {
    y = _y;

    y1 = y - radius;
    y2 = y + radius;
}
void RoundObj::setRadius(qint32 _radius) {
    radius = _radius;

    x1 = x - radius;
    y1 = y - radius;
    x2 = x + radius;
    y2 = y + radius;
}

bool RoundObj::isWithinCircle(qint32 _x, qint32 _y) const {
    return ((x - _x) * (x - _x) + (y - _y) * (y - _y)) <= (radius * radius);
}

qint32 RoundObj::getDistanceFormCenter(qint32 _x, qint32 _y) const {
    return (qint32) sqrt((x - _x) * (x - _x) + (y - _y) * (y - _y));
}