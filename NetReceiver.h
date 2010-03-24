/* 
 * File:   NetReceiver.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:44
 */

#ifndef _NETRECEIVER_H
#define	_NETRECEIVER_H

#include <QtNetwork>

#include "Receiver.h"

class NetReceiver : public Receiver {
public:
    NetReceiver();
    virtual ~NetReceiver();

    virtual Packet getPacket();

private:
    NetReceiver(const NetReceiver& orig) {} // disabled
};

#endif	/* _NETRECEIVER_H */

