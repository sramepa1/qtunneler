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

#ifndef _BASE_H
#define	_BASE_H

#include <QtGlobal>

#include "DefaultValues.h"

class Base {
public:
    Base(qint32 _x, qint32 _y, qint32 _width, qint32 _height, quint8 _color) : x1(_x), y1(_y), x2(_x + _width), y2(_y + _height), color(_color) {}
    virtual ~Base() {}

    virtual bool isWithinBase(qint32 _x, qint32 _y) const;
    
    qint32 x1;
    qint32 y1;
    qint32 x2;
    qint32 y2;

    /*        x1
     *      y1+---------+
     *        |         |
     *      h |         |
     *        |         |
     *        |         |
     *        +---------+y2
     *             w    x2
     */

    quint8 color;

private:
    Base(const Base& /*orig*/) {} // disabled
};

#endif	/* _BASE_H */

