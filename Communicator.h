/* 
 * File:   Communicator.h
 * Author: pavel
 *
 * Created on 7. duben 2010, 12:07
 */

#ifndef _COMMUNICATOR_H
#define	_COMMUNICATOR_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Communicator : public QObject {

    Q_OBJECT

public:
    Communicator(QObject* parent = NULL);
    virtual ~Communicator();

    QTcpServer* server;
    QTcpSocket* socket;
};

#endif	/* _COMMUNICATOR_H */

