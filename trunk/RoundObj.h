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
   
    //RoundObj(const RoundObj& orig) {} // implicit

    virtual ~RoundObj() {}

    /**
     * Check if given cooridantes colide witch circle
     */
    virtual bool isWithinCircle(quint32 _x, quint32 _y) const;

    /**
     * Get absolute value of distance (round down) form center.
     */
    virtual quint32 getDistanceFormCenter(quint32 _x, quint32 _y) const; //TODO refaktor name

    quint32 getX() const {return x;}
    quint32 getY() const {return y;}
    quint32 getRadius() const {return radius;}

    void setX(quint32 _x);
    void setY(quint32 _y);
    void setRadius(quint32 _radius);

    quint32 getX1() const {return x1;}
    quint32 getY1() const {return y1;}
    quint32 getX2() const {return x2;}
    quint32 getY2() const {return y2;}

    quint8 color;
    quint32 id;

protected:
    quint32 x1;
    quint32 y1;
    quint32 x2;
    quint32 y2;

    quint32 x;
    quint32 y;
    quint32 radius;
    
};

#endif	/* _ROUNDOBJ_H */

