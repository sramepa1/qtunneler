/* 
 * File:   PacketQueue.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:43
 */

#include "PacketQueue.h"

const Packet PacketQueue::peek() const {
    return queue.empty() ? Packet() : queue.first();
}

Packet PacketQueue::pop() {
    qDebug("PacketQueue: pop()");
    mutex.lock(); // very simple sync, deadlock can't happen
    Packet p = queue.dequeue();
    mutex.unlock();
    return p;
}

void PacketQueue::push(Packet p) {
    qDebug("PacketQueue: push()");
    mutex.lock();
    queue.enqueue(p);
    mutex.unlock();
    emit packetPushed();
}

bool PacketQueue::isEmpty() const {
    return queue.empty();
}
