/* 
 * File:   Stone.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:35
 */

#ifndef _STONE_H
#define	_STONE_H

#include "VectorObj.h"

class Stone : public VectorObj {
public:
    Stone();
    Stone(const Stone& orig);
    virtual ~Stone();
private:

};

#endif	/* _STONE_H */

