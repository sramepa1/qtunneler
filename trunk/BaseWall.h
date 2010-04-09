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
    BaseWall(quint32 _x, quint32 _y,quint32 _width, quint32 _heigth);
    BaseWall(const BaseWall& orig) : BitmapObj(orig) {}
    virtual ~BaseWall() {}
};

#endif	/* _BASEWALL_H */

