/*
 *      -----------------------------------------------
 *      QTunneler - a classic DOS game remake in QT
 *      -----------------------------------------------
 *
 *      semestral project for API programming course
 *      (Y36API) at the FEE CTU Prague
 *
 *      Created by:
 *           Pavel Sramek (sramepa1@fel.cvut.cz)
 *           Martin Smarda (smardmar@fel.cvut.cz)
 *
 *      March & April 2010
 *
 *      This is free software, licensed under GNU LGPL
 *      (GNU Lesser General Public License, version 3)
 *      http://www.gnu.org/licenses/lgpl.html
 *
 *      Project homepage:
 *      http://code.google.com/p/qtunneler/
 *
 *      Version 1.0
 *
 */

#include "NetReceiverThread.h"

#include <QtEndian>

NetReceiverThread::NetReceiverThread(QObject* parent, QTcpSocket* socket, PacketQueue* packetQueue) : QThread(parent) {
    sock = socket;
    queue = packetQueue;
    helper = NULL;
}

NetReceiverThread::~NetReceiverThread() {
    if(helper != NULL) delete helper;
}

void NetReceiverThread::run() {
    helper = new NetReceiverHelper(NULL, sock, queue);
    connect(sock,SIGNAL(readyRead()),helper,SLOT(readBytes()));
    exec();
}




NetReceiverHelper::NetReceiverHelper(QObject* parent, QTcpSocket* socket, PacketQueue* packetQueue) : QObject(parent), sock(socket), queue(packetQueue) {
    writeIndex = 0;
    buffer = new uchar[PACKET_BYTES];
}

NetReceiverHelper::~NetReceiverHelper() {
    delete[] buffer;
}

void NetReceiverHelper::readBytes() {
    //qDebug("NetThread: readBytes()");
    while(sock->bytesAvailable()) {
        sock->getChar((char*)(buffer + writeIndex));
        //qDebug("NetThread: Appending byte %d, value was %X",writeIndex,(uint)*((uchar*)(buffer + writeIndex)));
        writeIndex++;
        if(writeIndex >= PACKET_BYTES) {
            //qDebug("NetThread: pushing packet, opcode %d",qFromBigEndian(*((qint32*)(buffer))));
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
