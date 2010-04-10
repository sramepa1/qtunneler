/* 
 * File:   NetReceiver.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:44
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