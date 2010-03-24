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
    BaseWall(quint8 c):color(c) {}
    virtual ~BaseWall();

    virtual quint32 getColor() const {return color;}

protected:
    quint32 color;

private:
    BaseWall(const BaseWall& orig) {} // disabled
};

#endif	/* _BASEWALL_H */

