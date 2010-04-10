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
    BaseWall(qint32 _x, qint32 _y,qint32 _width, qint32 _heigth);
    BaseWall(const BaseWall& orig) : BitmapObj(orig) {}
    virtual ~BaseWall() {}
};

#endif	/* _BASEWALL_H */

