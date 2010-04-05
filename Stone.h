/* 
 * File:   Stone.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:35
 */

#ifndef _STONE_H
#define	_STONE_H

#include "BitmapObj.h"
#include "DefaultValues.h"

class Stone : public BitmapObj {
public:
    Stone();
    virtual ~Stone();

protected:
    Stone(const Stone& orig) : BitmapObj(orig) {} // disabled
};

#endif	/* _STONE_H */

