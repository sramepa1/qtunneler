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
    Base(quint8 color,qint32 x,qint32 y,quint32 width, quint32 height);
    virtual ~Base();
    
    virtual float getCircleOverlap(qint32 x, qint32 y, quint32 radius) const; // vrati 0..1
    virtual quint8 getColor() const {return color;}

protected:
    qint32 x1;
    qint32 y1;
    qint32 x2;
    qint32 y2;

    quint32 color;

private:
    Base(const Base& orig) {} // disabled
};

#endif	/* _BASE_H */

