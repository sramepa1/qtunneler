/* 
 * File:   QueueSender.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:47
 */

#ifndef _QUEUESENDER_H
#define	_QUEUESENDER_H

#include "Sender.h"
#include "PacketQueue.h"

class QueueSender : public Sender {

    Q_OBJECT

public:
    QueueSender(QObject* parent = NULL, PacketQueue* packetQueue = NULL): Sender(parent), queue(packetQueue) {}
    virtual ~QueueSender() {}

    virtual void sendPacket(Packet p) { queue->push(p); qDebug("QueueSender: sending %d",p.opcode); }

protected:

    // not owner
    PacketQueue* queue;

};

#endif	/* _QUEUESENDER_H */

