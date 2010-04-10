/* 
 * File:   NetReceiver.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:44
 */

#include "NetReceiver.h"

NetReceiver::NetReceiver(QObject* parent, QTcpSocket* socket) : Receiver(parent) {
    sock = socket;
}

NetReceiver::~NetReceiver() {
}


Packet NetReceiver::getPacket() {

    //TODO

    return Packet();
}

bool NetReceiver::hasPacketReady() {

    //TODO

    return false;
}
