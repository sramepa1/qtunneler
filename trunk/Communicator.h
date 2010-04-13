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

#ifndef _COMMUNICATOR_H
#define	_COMMUNICATOR_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>


// this is more or less just a convenience struct...

class Communicator : public QObject {

    Q_OBJECT

public:
    Communicator(QObject* parent = NULL) : QObject(parent) {
        socket = new QTcpSocket(this);
        server = new QTcpServer(this);
    }

    virtual ~Communicator() {}

    QTcpServer* server;
    QTcpSocket* socket;
};

#endif	/* _COMMUNICATOR_H */

