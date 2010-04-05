/* 
 * File:   VectorObj.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:35
 */

#ifndef _VECTOROBJ_H
#define	_VECTOROBJ_H

#include <QtCore>
#include "DefaultValues.h"

class BitmapObj {
public:
    BitmapObj();
    BitmapObj(quint32 _x, quint32 _y,quint32 _width, quint32 _heigth);


    virtual ~BitmapObj();

    quint32 getWrapperX1() const {return x;}
    quint32 getWrapperY1() const {return y;}
    quint32 getWrapperX2() const {return x + width;}
    quint32 getWrapperY2() const {return y + height;}
    quint32 getWrapperWidth() const {return width;}
    quint32 getWrapperHeight() const {return height;}
    
    virtual bool getXY(quint32 x, quint32 y) const;
    virtual quint8 getByte(quint32 xDiv8, quint32 y) const;

    virtual void setXY(quint32 x, quint32 y, bool val);
    virtual void setByte(quint32 xDiv8, quint32 y, quint8 val);
    
protected:
    quint32 x;
    quint32 y;
    quint32 width;
    quint32 height;

    /*                  x2
     *        +---------+y2
     *        |         |
     *      h |         |
     *        |         |
     *        |         |
     *      y1+---------+
     *        x1   w
     */

     quint8** bitmap;


    BitmapObj(const BitmapObj& orig) {} // disabled
};

#endif	/* _VECTOROBJ_H */

