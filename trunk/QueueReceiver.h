/* 
 * File:   QueueReceiver.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:45
 */

#ifndef _QUEUERECEIVER_H
#define	_QUEUERECEIVER_H

#include "Receiver.h"
#include "PacketQueue.h"

class QueueReceiver : public Receiver {

    Q_OBJECT

public:
    QueueReceiver(QObject* parent = NULL, PacketQueue* packetQueue = NULL);
    virtual ~QueueReceiver() {}

    virtual bool hasPacketReady();
    virtual Packet getPacket();

public slots:
    virtual void packetPushed();

protected:

    // owner and parent
    PacketQueue* queue;

};

#endif	/* _QUEUERECEIVER_H */

