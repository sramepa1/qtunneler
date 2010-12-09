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

#ifndef _BORDER_H
#define	_BORDER_H

#include "DefaultValues.h"
#include "RoundObj.h"

/**
 * This class represents the rectangle-shaped border of the gameplay area.
 */
class Border{
public:
    Border();
    virtual ~Border() {}
    
    virtual bool isBorderCollision(qint32 _x, qint32 _y) const;
    virtual bool isBorderCollision(const RoundObj * obj) const;

    //Border is represented by substrastion of matrix and this squere

    qint32 x1;
    qint32 y1;
    qint32 x2;
    qint32 y2;

private:
    Border(const Border& /*orig*/) {} // disabled
};

#endif	/* _BORDER_H */

