/* 
 * File:   NetSender.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:47
 */

#include "NetSender.h"
#include <QtEndian>

NetSender::NetSender(QObject* parent, QTcpSocket* socket) : Sender(parent) {
    sock = socket;
    buffer = new char[PACKET_BYTES];
}

void NetSender::sendPacket(Packet p) {

    qToBigEndian(p.opcode,(uchar*)buffer);
    qToBigEndian(p.timecode,(uchar*)(buffer + 4));
    qToBigEndian(p.data1,(uchar*)(buffer + 8));
    qToBigEndian(p.data2,(uchar*)(buffer + 12));
    qToBigEndian(p.data3,(uchar*)(buffer + 16));

    qDebug("NetSender: sending opcode %d, bigendian %X",p.opcode,*((quint32*)buffer));
    qDebug("NetSender: sending timecode %d, bigendian %X",p.timecode,*((quint32*)(buffer+4)));
    qDebug("NetSender: sending data1 %d, bigendian %X",p.data1,*((quint32*)(buffer+8)));
    qDebug("NetSender: sending data2 %d, bigendian %X",p.data2,*((quint32*)(buffer+12)));
    qDebug("NetSender: sending data3 %d, bigendian %X",p.data3,*((quint32*)(buffer+16)));
    sock->write(buffer,PACKET_BYTES);
}
