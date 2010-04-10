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
    PacketQueue(QObject* parent = NULL) : QObject(parent) {}
    virtual ~PacketQueue() { mutex.unlock(); }

    virtual void push(Packet p);
    virtual Packet pop();

    virtual const Packet peek() const;
    virtual bool isEmpty() const;

signals:
    virtual void packetPushed();

protected:
    QQueue<Packet> queue;
    
    QMutex mutex;

};

#endif	/* _PACKETQUEUE_H */

