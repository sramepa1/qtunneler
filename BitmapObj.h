/* 
 * File:   VectorObj.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:35
 */

#ifndef _VECTOROBJ_H
#define	_VECTOROBJ_H

#include <QtCore>
#include <QBitmap>
#include <QColor>
#include "DefaultValues.h"

class BitmapObj {
public:
    BitmapObj(quint32 _x = 0, quint32 _y = 0,quint32 _width = 0, quint32 _heigth = 0);


    virtual ~BitmapObj();

    virtual quint32 getWrapperX1() const {return x;}
    virtual quint32 getWrapperY1() const {return y;}
    virtual quint32 getWrapperX2() const {return x + width;}
    virtual quint32 getWrapperY2() const {return y + height;}
    virtual quint32 getWrapperWidth() const {return width;}
    virtual quint32 getWrapperHeight() const {return height;}

    virtual const QBitmap* getQBitmap() const {return &qbitmap;}
    virtual const QColor getColor() const {return color;}
    
    virtual bool getXY(quint32 x, quint32 y) const;
    virtual quint8 getByte(quint32 xDiv8, quint32 y) const;

    virtual void setXY(quint32 x, quint32 y, bool val);
    virtual void setByte(quint32 xDiv8, quint32 y, quint8 val);


    
protected:
    quint32 x;
    quint32 y;
    quint32 width;
    quint32 height;

    /*        x1
     *      y1+---------+
     *        |         |
     *      h |         |
     *        |         |
     *        |         |
     *        +---------+y2
     *             w    x2
     */

     quint8** bitmap;
     
     QBitmap qbitmap;
     QColor color;      // TODO initialize!


    BitmapObj(const BitmapObj& orig) {} // disabled
};

#endif	/* _VECTOROBJ_H */

