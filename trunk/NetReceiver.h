/* 
 * File:   NetReceiver.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:44
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
    virtual ~NetReceiver() {}

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

