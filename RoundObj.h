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
    RoundObj(qint32 _x, qint32 _y, qint32 _radius,quint8 _color);
   
    //RoundObj(const RoundObj& orig) {} // implicit

    virtual ~RoundObj() {}

    /**
     * Check if given cooridantes colide witch circle
     */
    virtual bool isWithinCircle(qint32 _x, qint32 _y) const;

    /**
     * Get absolute value of distance (round down) form center.
     */
    virtual qint32 getDistanceFormCenter(qint32 _x, qint32 _y) const;

    qint32 getX() const {return x;}
    qint32 getY() const {return y;}
    qint32 getRadius() const {return radius;}

    void setX(qint32 _x);
    void setY(qint32 _y);
    void setRadius(qint32 _radius);

    qint32 getX1() const {return x1;}
    qint32 getY1() const {return y1;}
    qint32 getX2() const {return x2;}
    qint32 getY2() const {return y2;}

    quint8 color;

protected:
    qint32 x1;
    qint32 y1;
    qint32 x2;
    qint32 y2;

    qint32 x;
    qint32 y;
    qint32 radius;
    
};

#endif	/* _ROUNDOBJ_H */

