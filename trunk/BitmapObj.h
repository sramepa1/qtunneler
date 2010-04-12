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

class BitmapObj{ //TODO copy constructor
public:
    BitmapObj(qint32 _x = 0, qint32 _y = 0, qint32 _width = 0, qint32 _height = 0);
    BitmapObj(const BitmapObj & orig);

    virtual ~BitmapObj();

    virtual qint32 getX1() const {return x;}
    virtual qint32 getY1() const {return y;}
    virtual qint32 getX2() const {return x + width;}
    virtual qint32 getY2() const {return y + height;}
    virtual qint32 getWidth() const {return width;}
    virtual qint32 getHeight() const {return height;}

    virtual const QBitmap* getQBitmap();
    virtual const QColor getColor() const {return color;}
    
    virtual bool getXY(qint32 x, qint32 y) const;
    virtual bool getXYGlobalCoordiantes(qint32 _x, qint32 _y) const;

    virtual quint8 getByte(qint32 xDiv8, qint32 y) const;

    virtual void setXY(qint32 x, qint32 y, bool val);
    virtual void setXYGlobalCoordiantes(qint32 _x, qint32 _y, bool val);

    virtual void setByte(qint32 xDiv8, qint32 y, quint8 val);
    
protected:
    qint32 x;
    qint32 y;
    qint32 width;
    qint32 height;

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
     
     QBitmap* qbitmap;
     QColor color;      // initialized in subclasses;

};

#endif	/* _VECTOROBJ_H */

