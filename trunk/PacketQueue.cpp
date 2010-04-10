/* 
 * File:   PacketQueue.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:43
 */

#include "PacketQueue.h"


// TODO don't forget synchronization / mutex <<<<<<<<<<<<<<<<<<<<<<


PacketQueue::PacketQueue(QObject* parent) : QObject(parent) {
}

PacketQueue::~PacketQueue() {
}

Packet PacketQueue::peek() const {

    //TODO

    return Packet();
}

Packet PacketQueue::pop() {

    //TODO

    return Packet();
}

void PacketQueue::push(Packet p) {

    //TODO

}
