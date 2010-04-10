/* 
 * File:   PacketQueue.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:43
 */

#ifndef _PACKETQUEUE_H
#define	_PACKETQUEUE_H

#include <QtCore>
#include "Packet.h"

// Synchronized class, needs mutex

class PacketQueue : public QObject {

    Q_OBJECT

public:
    PacketQueue(QObject* parent = NULL);
    virtual ~PacketQueue();

    virtual void push(Packet p);
    virtual Packet pop();
    virtual Packet peek() const;

protected:
    QQueue<Packet> queue;
    
    QMutex mutex;

};

#endif	/* _PACKETQUEUE_H */

