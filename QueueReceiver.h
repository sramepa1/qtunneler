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

