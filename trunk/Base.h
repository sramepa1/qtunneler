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
    Base(int i,int x,int y,int width, int height);
    virtual ~Base();
    
    virtual float getCircleOverlap(int x, int y, int radius) const; // vrati 0..1
    virtual int getColor() const {return color;}

private:
    int x1;
    int y1;
    int x2;
    int y2;

    int color;

    Base(const Base& orig);
};

#endif	/* _BASE_H */

