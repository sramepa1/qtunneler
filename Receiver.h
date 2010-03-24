/* 
 * File:   Receiver.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:44
 */

#ifndef _RECEIVER_H
#define	_RECEIVER_H

#include "Packet.h"


// interface

class Receiver {
public:
    Receiver() {}
    virtual ~Receiver() {}

    virtual Packet getPacket() =0;

private:
    QueueSender(const QueueSender& orig) {} // disabled
};

#endif	/* _RECEIVER_H */

