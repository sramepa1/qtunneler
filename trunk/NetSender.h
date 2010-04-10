/* 
 * File:   NetSender.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:47
 */

#ifndef _NETSENDER_H
#define	_NETSENDER_H

#include <QtNetwork>

#include "Sender.h"

class NetSender : public Sender {

    Q_OBJECT

public:
    NetSender(QObject* parent = NULL, QTcpSocket* socket = NULL);
    virtual ~NetSender();

    virtual void sendPacket(Packet p);

protected:

    //not owner
    QTcpSocket* sock;
};

#endif	/* _NETSENDER_H */

