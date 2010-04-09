/* 
 * File:   OrientedVectorObj.h
 * Author: rh
 *
 * Created on 2. duben 2010, 13:36
 */

#ifndef _ORIENTEDVECTOROBJ_H
#define	_ORIENTEDVECTOROBJ_H

#include "RoundObj.h"
#include "DefaultValues.h"

/* Round object's rotation
 *
 *         7  0  1
 *          \ | /
 *        6 - + - 2
 *          / | \
 *         5  4  3
 */

enum direction {
    NORTH, NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST
};

class OrientedRoundObj : public RoundObj {
public:
    OrientedRoundObj(quint32 x, quint32 y, quint32 radius, quint8 color, quint32 id, direction _rotation) : RoundObj(x, y, radius, color, id), rotation(_rotation) {}
    //OrientedRoundObj(const OrientedRoundObj& orig) : RoundObj(orig) {} // implicit
    virtual ~OrientedRoundObj();

    virtual QPair<quint32, quint32> getMoveCoorinates(qint32 steps = 1);
    virtual void move(qint32 steps = 1);

    direction rotation;
    
};

#endif	/* _ORIENTEDVECTOROBJ_H */

