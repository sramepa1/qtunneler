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

#ifndef _QUEUESENDER_H
#define	_QUEUESENDER_H

#include "Sender.h"
#include "PacketQueue.h"

class QueueSender : public Sender {

    Q_OBJECT

public:
    QueueSender(QObject* parent = NULL, PacketQueue* packetQueue = NULL): Sender(parent), queue(packetQueue) {}
    virtual ~QueueSender() {}

    virtual void sendPacket(Packet p) { queue->push(p); }

    virtual void flush() {}

protected:

    // not owner
    PacketQueue* queue;

};

#endif	/* _QUEUESENDER_H */

