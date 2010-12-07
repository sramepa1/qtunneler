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


PacketQueue::~PacketQueue() {
    mutex.unlock();
    
#ifdef DEBUG
    qDebug() << "Mutex PacketQueue unlocked at" << __FILE__ << __LINE__;
#endif
}


const Packet PacketQueue::peek() const {
    return queue.empty() ? Packet() : queue.first();
}

Packet PacketQueue::pop() {
    //qDebug("PacketQueue: pop()");

#ifdef DEBUG
    if(mutex.tryLock() == false){
        qDebug() << "Possible deadlock at" << __FILE__ << __LINE__;
        mutex.lock();
    }
#else
    mutex.lock();
#endif
#ifdef DEBUG
    qDebug() << "Mutex PacketQueue locked at" << __FILE__ << __LINE__;
#endif

    Packet p = queue.dequeue();
    mutex.unlock();

#ifdef DEBUG
    qDebug() << "Mutex PacketQueue unlocked at" << __FILE__ << __LINE__;
#endif

    return p;
}

void PacketQueue::push(Packet p) {
#ifdef DEBUG
    if(mutex.tryLock() == false){
        qDebug() << "Possible deadlock at" << __FILE__ << __LINE__;
        mutex.lock();
    }
#else
    mutex.lock();
#endif
#ifdef DEBUG
    qDebug() << "Mutex PacketQueue locked at" << __FILE__ << __LINE__;
#endif
    
    queue.enqueue(p);
    mutex.unlock();

#ifdef DEBUG
    qDebug() << "Mutex PacketQueue unlocked at" << __FILE__ << __LINE__;
#endif

    emit packetPushed();
}

bool PacketQueue::isEmpty() const {
    return queue.empty();
}
