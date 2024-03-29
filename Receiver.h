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

#ifndef _RECEIVER_H
#define	_RECEIVER_H

#include <QObject>

#include "Packet.h"


// interface

class Receiver : public QObject {

    Q_OBJECT

public:
    Receiver(QObject* parent = NULL) : QObject(parent) {}
    virtual ~Receiver() {}

    virtual bool hasPacketReady() =0;
    virtual Packet getPacket() =0;

signals:
    void packetReady(Receiver* self);
};

#endif	/* _RECEIVER_H */

