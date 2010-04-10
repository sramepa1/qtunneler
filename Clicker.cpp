/* 
 * File:   Clicker.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:43
 */

#include "Clicker.h"

Clicker::Clicker(QObject* parent) : QObject(parent) {
    sender = NULL;
}

Clicker::~Clicker() {
    if(sender != NULL) delete sender;
}

void Clicker::resetSender(Sender* s) {
    if(sender != NULL) delete sender;
    sender = s;
}

void Clicker::startClock() {
    time.setHMS(0,0,0,0);
    time.start();
}

void Clicker::confirmInitEnd() {
    sender->sendPacket(Packet(OP_INIT_CONFIRM));
}
