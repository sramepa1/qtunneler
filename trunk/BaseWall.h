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

#ifndef _BASEWALL_H
#define	_BASEWALL_H

#include "BitmapObj.h"
#include "DefaultValues.h"

class BaseWall : public BitmapObj {
public:
    BaseWall(qint32 _x, qint32 _y,qint32 _width, qint32 _height, QColor _color);
    BaseWall(const BaseWall& orig) : BitmapObj(orig) {}
    virtual ~BaseWall() {}
};

#endif	/* _BASEWALL_H */

