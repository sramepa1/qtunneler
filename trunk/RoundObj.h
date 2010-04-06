/* 
 * File:   RoundObj.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:38
 */

#ifndef _ROUNDOBJ_H
#define	_ROUNDOBJ_H

#include <QtCore>
#include "DefaultValues.h"

class RoundObj {
public:
    quint32 x;
    quint32 y;
    
    RoundObj(quint32 _x, quint32 _y, quint8 _color, quint32 _id) : x(_x), y(_y), color(_color), id(_id) {}
    virtual ~RoundObj();

    quint8 color;
    quint32 id;

    RoundObj(const RoundObj& orig) {} // disabled
};

#endif	/* _ROUNDOBJ_H */

