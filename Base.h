/* 
 * File:   Base.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:38
 */

#ifndef _BASE_H
#define	_BASE_H

class Base {
public:
    Base(quint8 _color,quint32 x,quint32 y,quint32 width, quint32 height) : color(_color), x1(x), y1(y), x2(x + width), y2(y + height) {}
    virtual ~Base();
    
    virtual qreal getCircleOverlap(quint32 x, quint32 y, quint32 radius) const; // vrati 0..1
    virtual quint8 getColor() const {return color;}

protected:
    quint32 x1;
    quint32 y1;
    quint32 x2;
    quint32 y2;

    quint8 color;

private:
    Base(const Base& orig) {} // disabled
};

#endif	/* _BASE_H */

