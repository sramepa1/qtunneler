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
    
    RoundObj(int i) : color(i) {}
    virtual ~RoundObj();

    virtual int getColor() const {return color;}

private:
    int color;

    RoundObj(const RoundObj& orig);
};

#endif	/* _ROUNDOBJ_H */

