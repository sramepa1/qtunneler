/*
 *      -----------------------------------------------
 *      QTunneler - a classic DOS game remake in QT
 *      -----------------------------------------------
 *
 *      semestral project for API programming course
 *      (Y36API) at the FEE CTU Prague
 *
 *      Created by:
 *           Pavel Sramek (sramepa1@fel.cvut.cz)
 *           Martin Smarda (smardmar@fel.cvut.cz)
 *
 *      March & April 2010
 *
 *      This is free software, licensed under GNU LGPL
 *      (GNU Lesser General Public License, version 3)
 *      http://www.gnu.org/licenses/lgpl.html
 *
 *      Project homepage:
 *      http://code.google.com/p/qtunneler/
 *
 *      Version 1.0
 *
 */

#ifndef _STONE_H
#define	_STONE_H

#include "BitmapObj.h"
#include "DefaultValues.h"

class Stone : public BitmapObj {
public:
    
    /**
     * _width MUST be divisible by 8
     */
    Stone(qint32 _x, qint32 _y, qint32 _width, qint32 _height);
    
    virtual ~Stone() {}

};

#endif	/* _STONE_H */

