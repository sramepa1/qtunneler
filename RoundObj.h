/* 
 * File:   RoundObj.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:38
 */

#ifndef _ROUNDOBJ_H
#define	_ROUNDOBJ_H

class RoundObj {
public:
    int x;
    int y;
    
    RoundObj(int c, int i) : color(c),id(i) {}
    virtual ~RoundObj();

    virtual int getColor() const {return color;}
    virtual int getID() const {return id;}

protected:
    int color;
    int id;

private:
    RoundObj(const RoundObj& orig) {} // disabled
};

#endif	/* _ROUNDOBJ_H */

