/* 
 * File:   NetReceiverThread.h
 * Author: pavel
 *
 * Created on 10. duben 2010, 13:22
 */

#ifndef _NETRECEIVERTHREAD_H
#define	_NETRECEIVERTHREAD_H

#include <QThread>
#include <QTcpSocket>

#include "DefaultValues.h"
#include "PacketQueue.h"

class NetReceiverThread : public QThread {

    Q_OBJECT

public:
    NetReceiverThread(QObject* parent = NULL, QTcpSocket* socket = NULL, PacketQueue* packetQueue = NULL);
    virtual ~NetReceiverThread();

    virtual void run();

public slots:
    virtual void readBytes();

protected:

    uchar* buffer;
    int writeIndex;

    // not owner:
    QTcpSocket* sock;
    PacketQueue* queue;
};

#endif	/* _NETRECEIVERTHREAD_H */

