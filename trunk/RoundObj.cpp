/* 
 * File:   RoundObj.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:38
 */

#include "RoundObj.h"

void RoundObj::setX(quint32 _x) {
    x = _x;

    x1 = x - radius;
    x2 = x + radius;
}
void RoundObj::setY(quint32 _y) {
    y = _y;

    y1 = y - radius;
    y2 = y + radius;
}
void RoundObj::setRadius(quint32 _radius) {
    radius = _radius;

    x1 = x - radius;
    y1 = y - radius;
    x2 = x + radius;
    y2 = y + radius;
}

bool RoundObj::isWithinCircle(quint32 _x, quint32 _y) const {
    return ((x - _x) * (x - _x) + (y - _y) * (y - _y)) <= (radius * radius);
}

quint32 RoundObj::getDistanceFormCenter(quint32 _x, quint32 _y) const {
    return (quint32) sqrt((x - _x) * (x - _x) + (y - _y) * (y - _y));
}