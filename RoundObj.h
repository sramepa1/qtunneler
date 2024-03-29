/*
 *      -----------------------------------------------
 *      QTunneler - a classic DOS game remake in QT
 *      -----------------------------------------------
 *
 *      semestral project for API programming course
 *      (Y36API) at the FEE CTU Prague
 *
 *      Created by:
 *           Pavel Sramek (sramepa1@fel.cvut.cz)
 *           Martin Smarda (smardmar@fel.cvut.cz)
 *
 *      March & April 2010
 *
 *      This is free software, licensed under GNU LGPL
 *      (GNU Lesser General Public License, version 3)
 *      http://www.gnu.org/licenses/lgpl.html
 *
 *      Project homepage:
 *      http://code.google.com/p/qtunneler/
 *
 *      Version 1.0
 *
 */

#ifndef _ROUNDOBJ_H
#define	_ROUNDOBJ_H

#include <QtCore>
#include "DefaultValues.h"

/**
 * This class represent general round object.
 */
class RoundObj {
public:
    RoundObj(qint32 _x, qint32 _y, qint32 _radius,quint8 _color);
   
    //RoundObj(const RoundObj& orig) {} // implicit

    virtual ~RoundObj() {}

    virtual bool isWithinCircle(qint32 _x, qint32 _y) const;
    virtual qint32 getDistanceFormCenter(qint32 _x, qint32 _y) const;

    virtual qint32 getX() const {return x;}
    virtual qint32 getY() const {return y;}
    virtual qint32 getRadius() const {return radius;}

    virtual void setX(qint32 _x);
    virtual void setY(qint32 _y);
    virtual void setRadius(qint32 _radius);

    virtual qint32 getX1() const {return x1;}
    virtual qint32 getY1() const {return y1;}
    virtual qint32 getX2() const {return x2;}
    virtual qint32 getY2() const {return y2;}

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

