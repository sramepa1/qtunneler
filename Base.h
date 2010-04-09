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
    Base(quint32 _x, quint32 _y, quint32 _width, quint32 _height, quint8 _color) : color(_color), x1(_x), y1(_y), x2(_x + _width), y2(_y + _height) {}
    virtual ~Base() {}

    virtual bool isWithinBase(quint32 _x, quint32 _y) const;
    
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

