/* 
 * File:   Communicator.h
 * Author: pavel
 *
 * Created on 7. duben 2010, 12:07
 */

#ifndef _COMMUNICATOR_H
#define	_COMMUNICATOR_H

#include <QObject>

class Communicator : public QObject {

    Q_OBJECT

public:
    Communicator(QObject* parent = NULL);
    virtual ~Communicator();

    QTcpServer* server;
    QTcpSocket* socket;
};

#endif	/* _COMMUNICATOR_H */

