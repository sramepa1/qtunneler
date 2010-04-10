/* 
 * File:   QueueSender.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:47
 */

#include "QueueSender.h"

QueueSender::QueueSender(QObject* parent, PacketQueue* packetQueue) : Sender(parent) {
    queue = packetQueue;
}

QueueSender::~QueueSender() {
}

void QueueSender::sendPacket(Packet p) {

    //TODO

}
