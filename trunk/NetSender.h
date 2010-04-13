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

#ifndef _NETSENDER_H
#define	_NETSENDER_H

#include <QtNetwork>
#include "DefaultValues.h"
#include "Sender.h"

class NetSender : public Sender {

    Q_OBJECT

public:
    NetSender(QObject* parent = NULL, QTcpSocket* socket = NULL);
    virtual ~NetSender() { delete[] buffer; }

    virtual void sendPacket(Packet p);
    virtual void flush();

protected:

    //not owner
    QTcpSocket* sock;

    char* buffer;
};

#endif	/* _NETSENDER_H */

