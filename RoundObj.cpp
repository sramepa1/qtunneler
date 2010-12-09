/* 
 * File:   RoundObj.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:38
 */

#include "RoundObj.h"

/**
 * Constructs the round object.
 *
 * @param _x
 * @param _y
 * @param _radius
 * @param _color
 */
RoundObj::RoundObj(qint32 _x, qint32 _y, qint32 _radius, quint8 _color) : color(_color), x(_x), y(_y), radius(_radius) {
    x1 = x - radius;
    y1 = y - radius;
    x2 = x + radius;
    y2 = y + radius;
}

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

/**
 * Check if given point colides with round object.
 *
 * @param _x
 * @param _y
 * @return
 */
bool RoundObj::isWithinCircle(qint32 _x, qint32 _y) const {
    return ((x - _x) * (x - _x) + (y - _y) * (y - _y)) <= (radius * radius);
}

/**
 * Get absolute value of distance from round object's center.
 *
 * @param _x
 * @param _y
 * @return
 */
qint32 RoundObj::getDistanceFormCenter(qint32 _x, qint32 _y) const {
    return (qint32) sqrt((x - _x) * (x - _x) + (y - _y) * (y - _y));
}