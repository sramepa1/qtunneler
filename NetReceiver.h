/* 
 * File:   NetReceiver.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:44
 */

#ifndef _NETRECEIVER_H
#define	_NETRECEIVER_H

#include "Receiver.h"

class NetReceiver : public Receiver {
public:
    NetReceiver();
    NetReceiver(const NetReceiver& orig);
    virtual ~NetReceiver();
private:

};

#endif	/* _NETRECEIVER_H */

