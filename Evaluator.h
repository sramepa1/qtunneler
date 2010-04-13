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

#ifndef _EVALUATOR_H
#define	_EVALUATOR_H

#include <QtCore>
#include <QObject>

#include "PacketQueue.h"
#include "Receiver.h"
#include "Sender.h"
#include "Model.h"

class Evaluator : public QThread {

    Q_OBJECT

public:
    Evaluator(QObject* parent = NULL);
    virtual ~Evaluator();

    virtual void run();

    virtual void addSender(Sender* s);
    virtual void addReceiver(Receiver* r);    
    
public slots:

    // clear model, generate all world data AND send to all clients via packet dispatch
    // when world confirmed by all clients, dispatches start packets and enters evaluation/dispatch state machine
    virtual void generateWorldAndStartRound();

    // Stop thread, dump queue contents, timer, senders and receivers
    virtual void clearStateAndStop();

protected slots:

    virtual void handlePacket(Receiver* r);

    virtual void evaluateState();

signals:


protected:

    virtual void dispatchPacket(Packet& packet);
    virtual void flushPacketList();

    virtual void dumpSendersAndReceivers();


    virtual void handleTankMovementChange(int tankID, int newDirection);
    virtual void handleTankShootChange(int tankID, int newState);

    //destruct projectile
    QHash<qint32, Tank *> deletedTanks;
    QHash<qint32, Projectile *> deletedProjectiles;
    void explode(Projectile * obj);
    void explode(Tank * obj);

    // owner! this is a separate model because of sync problems (one frame ahead) and thread safety
    Model* model;

    QLinkedList<Packet> list;
    QLinkedList<Packet> tempList;

    QVector<Receiver*> receivers;
    QVector<Sender*> senders;

    int readyCnt;

    QTimer timer;

private:
    Evaluator(const Evaluator& /*orig*/) : QThread() {} // disabled
};

#endif	/* _EVALUATOR_H */

