/* 
 * File:   Sender.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:46
 */

#ifndef _SENDER_H
#define	_SENDER_H

#include "Packet.h"


// interface

class Sender {
public:
    Sender() {}
    virtual ~Sender() {}

    virtual void sendPacket(Packet p) =0;

private:
    Sender(const Sender& orig) {} // disabled
};

#endif	/* _SENDER_H */

