/* 
 * File:   RoundObj.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:38
 */

#ifndef _ROUNDOBJ_H
#define	_ROUNDOBJ_H

#include <QtCore>
#include "DefaultValues.h"

class RoundObj {
public:
    RoundObj(quint32 _x, quint32 _y, quint32 _radius,quint8 _color, quint32 _id) : x(_x), y(_y), radius(_radius), color(_color), id(_id) {}
    virtual ~RoundObj() {}

    /**
     * Check if given cooridantes colide witch circle
     */
    virtual bool isWithinCircle(quint32 _x, quint32 _y); //TODO refaktor name

    /**
     * Get absolute value of distance (round down) form center.
     */
    virtual quint32 getDistanceFormCenter(quint32 _x, quint32 _y); //TODO refaktor name

    quint32 x;
    quint32 y;
    quint32 radius;

    quint8 color;
    quint32 id;
    
protected:
    RoundObj(const RoundObj& orig) {} // disabled
};

#endif	/* _ROUNDOBJ_H */

