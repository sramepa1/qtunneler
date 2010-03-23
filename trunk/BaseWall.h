/* 
 * File:   BaseWall.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:37
 */

#ifndef _BASEWALL_H
#define	_BASEWALL_H

#include "VectorObj.h"

class BaseWall : public VectorObj {
public:
    BaseWall(int i):color(i){}
    virtual ~BaseWall();

    virtual int getColor() const {return color;}

private:
    int color;
    
    BaseWall(const BaseWall& orig);
};

#endif	/* _BASEWALL_H */

