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
    //NOT supported yet

    Stone();
    Stone(const Stone& orig) : BitmapObj(orig) {}

    virtual ~Stone();

};

#endif	/* _STONE_H */
