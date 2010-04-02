/* 
 * File:   Stone.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:35
 */

#ifndef _STONE_H
#define	_STONE_H

#include "VectorObj.h"
#include "DefaultValues.h"

class Stone : public VectorObj {
public:
    Stone();
    virtual ~Stone();

private:
    Stone(const Stone& orig) {} // disabled
};

#endif	/* _STONE_H */

