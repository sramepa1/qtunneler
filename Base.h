/* 
 * File:   Base.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:38
 */

#ifndef _BASE_H
#define	_BASE_H

#include "DefaultValues.h"

class Base {
public:
    Base(quint8 _color,quint32 x,quint32 y,quint32 width, quint32 height) : color(_color), x1(x), y1(y), x2(x + width), y2(y + height) {}
    virtual ~Base() {}
    
    virtual qreal getCircleOverlap(quint32 _x, quint32 _y, quint32 _radius) const; //TODO move to logic
    virtual quint8 getColor() const {return color;}

protected:
    quint32 x1;
    quint32 y1;
    quint32 x2;
    quint32 y2;

    /*                  x2
     *        +---------+y2
     *        |         |
     *        |         |
     *        |         |
     *        |         |
     *      y1+---------+
     *        x1
     */

    quint8 color;

private:
    Base(const Base& orig) {} // disabled
};

#endif	/* _BASE_H */

