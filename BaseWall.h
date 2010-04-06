/* 
 * File:   BaseWall.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:37
 */

#ifndef _BASEWALL_H
#define	_BASEWALL_H

#include "BitmapObj.h"
#include "DefaultValues.h"

class BaseWall : public BitmapObj {
public:
    BaseWall(quint8 _color) : color(_color) {}
    virtual ~BaseWall();

    quint32 color;

private:
    BaseWall(const BaseWall& orig) {} // disabled
};

#endif	/* _BASEWALL_H */

