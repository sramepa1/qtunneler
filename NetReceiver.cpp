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

#include "NetReceiver.h"

NetReceiver::NetReceiver(QObject* parent, QTcpSocket* socket) : Receiver(parent) {
    sock = socket;
    PacketQueue* q = new PacketQueue();
    thread = new NetReceiverThread(this,socket,q);
    queueRec = new QueueReceiver(this,q);
    connect(queueRec,SIGNAL(packetReady(Receiver*)),this,SLOT(packetRead(Receiver*)));
    thread->start();
}