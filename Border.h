/* 
 * File:   Border.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:36
 */

#ifndef _BORDER_H
#define	_BORDER_H

#include "VectorObj.h"

class Border : public VectorObj{
public:
    Border();
    virtual ~Border();

private:
    Border(const Border& orig) {} // disabled
};

#endif	/* _BORDER_H */

