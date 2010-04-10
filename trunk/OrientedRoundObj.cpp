/* 
 * File:   OrientedVectorObj.cpp
 * Author: rh
 * 
 * Created on 2. duben 2010, 13:36
 */

#include "OrientedRoundObj.h"

OrientedRoundObj::~OrientedRoundObj() {
}

QPair<qint32, qint32> OrientedRoundObj::getMoveCoorinates(qint32 steps){
    qint32 x = this->x;
    qint32 y = this->y;

    switch (rotation){
        case NORTH :
            y += steps;
            break;

        case NORTH_EAST :
            y += steps;

        case EAST :
            x += steps;
            break;

        case SOUTH_EAST :
            x += steps;

        case SOUTH :
            y -= steps;
            break;

        case SOUTH_WEST :
            y -= steps;

        case WEST :
            x -= steps;
            break;

        case NORTH_WEST :
            x -= steps;
            y += steps;
            break;
    }

    return QPair<qint32, qint32>(x, y);
}

void OrientedRoundObj::move(qint32 steps){
    QPair<qint32, qint32> pair = getMoveCoorinates(steps);
    x = pair.first;
    y = pair.second;
}


