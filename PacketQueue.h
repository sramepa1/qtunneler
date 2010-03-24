/* 
 * File:   PacketQueue.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:43
 */

#ifndef _PACKETQUEUE_H
#define	_PACKETQUEUE_H

#include <QtCore>

// TODO Synchronized class, needs mutexes

class PacketQueue {
public:
    PacketQueue();    
    virtual ~PacketQueue();

    virtual void push(Packet p);
    virtual Packet pop();
    virtual Packet peek() const;

protected:
    QQueue<Packet> queue;

private:
    PacketQueue(const PacketQueue& orig) {} // disabled
};

#endif	/* _PACKETQUEUE_H */

