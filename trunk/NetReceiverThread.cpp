/* 
 * File:   NetReceiverThread.cpp
 * Author: pavel
 * 
 * Created on 10. duben 2010, 13:22
 */

#include "NetReceiverThread.h"

#include <QtEndian>

NetReceiverThread::NetReceiverThread(QObject* parent, QTcpSocket* socket, PacketQueue* packetQueue) : QThread(parent), queue(packetQueue), sock(socket) {
    connect(sock,SIGNAL(readyRead()),this,SLOT(readBytes()));
    writeIndex = 0;
    buffer = new uchar[PACKET_BYTES];
}

NetReceiverThread::~NetReceiverThread() {
    delete[] buffer;
    quit();
    while(isRunning()) {}
}

void NetReceiverThread::run() {
    exec();
}

void NetReceiverThread::readBytes() {
    qDebug("NetThread: readBytes()");
    while(sock->bytesAvailable()) {
        sock->getChar((char*)(buffer + writeIndex));
        qDebug("NetThread: Appending byte %d, value was %X",writeIndex,(uint)*((uchar*)(buffer + writeIndex)));
        writeIndex++;
        if(writeIndex >= PACKET_BYTES) {
            qDebug("NetThread: pushing packet, opcode %d",qFromBigEndian(*((qint32*)(buffer))));
            writeIndex = 0;
            queue->push(Packet(
                qFromBigEndian(*((qint32*)buffer)),
                qFromBigEndian(*((qint32*)(buffer + 4))),
                qFromBigEndian(*((qint32*)(buffer + 8))),
                qFromBigEndian(*((qint32*)(buffer + 12))),
                qFromBigEndian(*((qint32*)(buffer + 16)))
            ));
        }
    }
}

