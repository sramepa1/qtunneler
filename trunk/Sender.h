/* 
 * File:   Sender.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:46
 */

#ifndef _SENDER_H
#define	_SENDER_H

#include <QObject>

#include "Packet.h"


// interface

class Sender : public QObject {

    Q_OBJECT

public:
    Sender(QObject* parent = NULL) : QObject(parent) {}
    virtual ~Sender() {}

    virtual void sendPacket(Packet p) =0;

private:
    Sender(const Sender& orig) {} // disabled
};

#endif	/* _SENDER_H */

