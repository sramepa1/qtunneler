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

    Q_OBJECT

public:
    NetReceiver(QObject* parent = NULL, QTcpSocket* socket = NULL);
    virtual ~NetReceiver();

    virtual bool hasPacketReady();
    virtual Packet getPacket();

protected:

    // not owner
    QTcpSocket* sock;

};

#endif	/* _NETRECEIVER_H */

