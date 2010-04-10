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
    connect(queue,SIGNAL(packetPushed()),this,SLOT(packetPushed()));
}

Packet QueueReceiver::getPacket() {
    qDebug("QueueReceiver: returning packet with opcode %d",queue->peek().opcode);
    return queue->isEmpty() ? Packet() : queue->pop();
}

bool QueueReceiver::hasPacketReady() {
    return !queue->isEmpty();
}

void QueueReceiver::packetPushed() {
    qDebug("QueueReceiver: packet pushed");
    emit packetReady(this);
}