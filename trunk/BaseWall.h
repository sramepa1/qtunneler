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
    BaseWall();
    BaseWall(const BaseWall& orig);
    virtual ~BaseWall();
private:

};

#endif	/* _BASEWALL_H */

