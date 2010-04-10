/* 
 * File:   NetSender.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:47
 */

#include "NetSender.h"

NetSender::NetSender(QObject* parent, QTcpSocket* socket) : Sender(parent) {
    sock = socket;
}

NetSender::~NetSender() {
}

void NetSender::sendPacket(Packet p) {

    //TODO
    
}
