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

    /*qDebug("NetSender: sending opcode %d, bigendian %X",p.opcode,*((quint32*)buffer));
    qDebug("NetSender: sending timecode %d, bigendian %X",p.timecode,*((quint32*)(buffer+4)));
    qDebug("NetSender: sending data1 %d, bigendian %X",p.data1,*((quint32*)(buffer+8)));
    qDebug("NetSender: sending data2 %d, bigendian %X",p.data2,*((quint32*)(buffer+12)));
    qDebug("NetSender: sending data3 %d, bigendian %X",p.data3,*((quint32*)(buffer+16)));*/
    sock->write(buffer,PACKET_BYTES);
}

void NetSender::flush() {
    sock->flush();
}
