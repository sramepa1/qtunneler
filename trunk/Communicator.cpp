/* 
 * File:   Communicator.cpp
 * Author: pavel
 * 
 * Created on 7. duben 2010, 12:07
 */

#include "Communicator.h"

Communicator::Communicator(QObject* parent) : QObject(parent) {
    socket = new QTcpSocket(this);
    server = new QTcpServer(this);
}


Communicator::~Communicator() {
}

