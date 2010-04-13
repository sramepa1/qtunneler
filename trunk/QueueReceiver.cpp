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

#include "QueueReceiver.h"

QueueReceiver::QueueReceiver(QObject* parent, PacketQueue* packetQueue) : Receiver(parent) {
    queue = packetQueue;
    queue->setParent(this);
    connect(queue,SIGNAL(packetPushed()),this,SLOT(packetPushed()));
}

Packet QueueReceiver::getPacket() {
    //qDebug("QueueReceiver: returning packet with opcode %d",queue->peek().opcode);
    return queue->isEmpty() ? Packet() : queue->pop();
}

bool QueueReceiver::hasPacketReady() {
    return !queue->isEmpty();
}

void QueueReceiver::packetPushed() {
    //qDebug("QueueReceiver: packet pushed");
    emit packetReady(this);
}