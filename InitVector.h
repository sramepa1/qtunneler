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

#ifndef _INITVECTOR_H
#define	_INITVECTOR_H

#include <QString>

/**
 * Class designed to store data given in @see InitDialog.
 */
struct InitVector {

    InitVector(bool _create, QString _port, QString _host = "") : host(_host), port(_port), create(_create) {}

    QString host;
    QString port;
    bool create;

};

#endif	/* _INITVECTOR_H */

