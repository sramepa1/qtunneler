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

#ifndef _PACKETQUEUE_H
#define	_PACKETQUEUE_H

#include <QtCore>
#include "Packet.h"

// Synchronized class, needs mutex

class PacketQueue : public QObject {

    Q_OBJECT

public:
    PacketQueue(QObject* parent = NULL) : QObject(parent) {}
    virtual ~PacketQueue();

    virtual void push(Packet p);
    virtual Packet pop();

    virtual const Packet peek() const;
    virtual bool isEmpty() const;

signals:
    void packetPushed();

protected:
    QQueue<Packet> queue;
    
    QMutex mutex;

};

#endif	/* _PACKETQUEUE_H */

