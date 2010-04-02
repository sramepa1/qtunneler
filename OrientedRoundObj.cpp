/* 
 * File:   OrientedVectorObj.cpp
 * Author: rh
 * 
 * Created on 2. duben 2010, 13:36
 */

#include "OrientedRoundObj.h"

OrientedRoundObj::~OrientedRoundObj() {
}

bool OrientedRoundObj::moveInDirection(quint32 steps){
    
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
}
