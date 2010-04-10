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
    QueueSender(QObject* parent = NULL, PacketQueue* packetQueue = NULL);
    virtual ~QueueSender();

    virtual void sendPacket(Packet p);

protected:

    // not owner
    PacketQueue* queue;

};

#endif	/* _QUEUESENDER_H */

