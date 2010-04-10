/* 
 * File:   QueueReceiver.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:45
 */

#include "QueueReceiver.h"

QueueReceiver::QueueReceiver(QObject* parent, PacketQueue* packetQueue) : Receiver(parent) {
    queue = packetQueue;
    queue->setParent(this);
}

QueueReceiver::~QueueReceiver() {
}

Packet QueueReceiver::getPacket() {

    //TODO

    return Packet();
}

bool QueueReceiver::hasPacketReady() {
    //TODO

    return true;
}