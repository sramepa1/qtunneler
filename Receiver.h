/* 
 * File:   Receiver.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:44
 */

#ifndef _RECEIVER_H
#define	_RECEIVER_H

#include <QObject>

#include "Packet.h"


// interface

class Receiver : public QObject {

    Q_OBJECT

public:
    Receiver(QObject* parent = NULL) : QObject(parent) {}
    virtual ~Receiver() {}

    virtual bool hasPacketReady() =0;
    virtual Packet getPacket() =0;

signals:
    virtual void packetReady(Receiver* self);
};

#endif	/* _RECEIVER_H */

