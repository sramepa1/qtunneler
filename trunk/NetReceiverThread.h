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

#ifndef _NETRECEIVERTHREAD_H
#define	_NETRECEIVERTHREAD_H

#include <QThread>
#include <QTcpSocket>

#include "DefaultValues.h"
#include "PacketQueue.h"

class NetReceiverHelper : public QObject {

    Q_OBJECT

public:
    NetReceiverHelper(QObject* parent = NULL, QTcpSocket* socket = NULL, PacketQueue* packetQueue = NULL);
    virtual ~NetReceiverHelper();

public slots:
    virtual void readBytes();

protected:

    uchar* buffer;
    int writeIndex;

    // not owner:
    QTcpSocket* sock;
    PacketQueue* queue;

};




class NetReceiverThread : public QThread {

    Q_OBJECT

public:
    NetReceiverThread(QObject* parent = NULL, QTcpSocket* socket = NULL, PacketQueue* packetQueue = NULL);
    virtual ~NetReceiverThread();

    virtual void run();

protected:
    
    NetReceiverHelper* helper;

    // not owner:
    QTcpSocket* sock;
    PacketQueue* queue;

};

#endif	/* _NETRECEIVERTHREAD_H */

