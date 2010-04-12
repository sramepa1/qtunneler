/* 
 * File:   OrientedVectorObj.cpp
 * Author: rh
 * 
 * Created on 2. duben 2010, 13:36
 */

#include "OrientedRoundObj.h"

#include <cmath>

OrientedRoundObj::~OrientedRoundObj() {
}

QPair<qint32, qint32> OrientedRoundObj::getMoveCoorinates(qint32 steps){
    qint32 x = this->x;
    qint32 y = this->y;
    qint32 diagonalSteps = (qint32)round(steps * M_SQRT1_2);

    switch (rotation){
        case NORTH :                            y -= steps;         break;
        case NORTH_EAST :   x += diagonalSteps; y -= diagonalSteps; break;
        case EAST :         x += steps;                             break;
        case SOUTH_EAST :   x += diagonalSteps; y += diagonalSteps; break;
        case SOUTH :                            y += steps;         break;
        case SOUTH_WEST :   x -= diagonalSteps; y += diagonalSteps; break;
        case WEST :         x -= steps;                             break;
        case NORTH_WEST :   x -= diagonalSteps; y -= diagonalSteps; break;
    }

    return QPair<qint32, qint32>(x, y);
}

void OrientedRoundObj::move(qint32 steps){
    QPair<qint32, qint32> pair = getMoveCoorinates(steps);
    x = pair.first;
    y = pair.second;
}


