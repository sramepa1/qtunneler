/* 
 * File:   Border.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:36
 */

#ifndef _BORDER_H
#define	_BORDER_H

#include "DefaultValues.h"
#include "RoundObj.h"

class Border{
public:
    Border();
    virtual ~Border() {}
    
    virtual bool isBorderCollision(quint32 _x, quint32 _y) const;
    virtual bool isBorderCollision(const RoundObj * obj) const;

    //Border is represented by substrastion of matrix and this squere

    quint32 x1;
    quint32 y1;
    quint32 x2;
    quint32 y2;

private:
    Border(const Border& orig) {} // disabled
};

#endif	/* _BORDER_H */

