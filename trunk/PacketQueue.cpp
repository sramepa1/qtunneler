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

#include "PacketQueue.h"

const Packet PacketQueue::peek() const {
    return queue.empty() ? Packet() : queue.first();
}

Packet PacketQueue::pop() {
    //qDebug("PacketQueue: pop()");
    mutex.lock(); // very simple sync, deadlock can't happen
    Packet p = queue.dequeue();
    mutex.unlock();
    return p;
}

void PacketQueue::push(Packet p) {
    //qDebug("PacketQueue: push()");
    mutex.lock();
    queue.enqueue(p);
    mutex.unlock();
    emit packetPushed();
}

bool PacketQueue::isEmpty() const {
    return queue.empty();
}
