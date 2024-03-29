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

#ifndef _NETRECEIVER_H
#define	_NETRECEIVER_H

#include <QtNetwork>

#include "Receiver.h"
#include "QueueReceiver.h"
#include "NetReceiverThread.h"

class NetReceiver : public Receiver {

    Q_OBJECT

public:
    NetReceiver(QObject* parent = NULL, QTcpSocket* socket = NULL);
    virtual ~NetReceiver() {
        thread->quit();
        while(thread->isRunning()) {}
        qDebug("NetReceiver terminated");
    }

    virtual bool hasPacketReady() { return queueRec->hasPacketReady(); }
    virtual Packet getPacket() { return queueRec->getPacket(); }

protected slots:
    virtual void packetRead(Receiver* /*rec*/) { emit packetReady(this); }

protected:

    // not owner
    QTcpSocket* sock;

    QueueReceiver* queueRec;
    NetReceiverThread* thread;

};

#endif	/* _NETRECEIVER_H */

