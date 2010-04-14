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
#include "QueueSender.h"
#include "NetSender.h"
#include "QueueReceiver.h"
#include "NetReceiver.h"

class Evaluator : public QObject {

    Q_OBJECT

public:
    Evaluator(QObject* parent = NULL);
    virtual ~Evaluator();

    virtual void addSender(Sender* s);
    virtual void addReceiver(Receiver* r);    
    
public slots:

    // clear model, generate all world data AND send to all clients via packet dispatch
    // when world confirmed by all clients, dispatches start packets and enters evaluation/dispatch state machine
    virtual void generateWorldAndStartRound();

    // dump queue contents, timer, senders and receivers
    virtual void clearStateAndStop();


    // init phase slots

    virtual void addNetReceiver(QTcpSocket* sock) {
        addReceiver(new NetReceiver(this,sock));
    }

    virtual void addNetSender(QTcpSocket* sock) {
        addSender(new NetSender(this, sock));
    }

    virtual void addQueueSender(PacketQueue* q) {
        addSender(new QueueSender(this, q));
    }

    virtual void addQueueReceiver(PacketQueue** queuePtr) {
        *queuePtr = new PacketQueue();
        addReceiver(new QueueReceiver(this,*queuePtr));
    }

protected slots:

    virtual void handlePacket(Receiver* r);

    virtual void evaluateState();

protected:

    virtual void dispatchPacket(Packet& packet);
    virtual void flushPacketList();

    virtual void dumpSendersAndReceivers();


    virtual void handleTankMovementChange(int tankID, int newDirection);
    virtual void handleTankShootChange(int tankID, int newState);

    //destruct projectile
    QHash<qint32, Tank *> hiddenTanks;
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
    Evaluator(const Evaluator& /*orig*/) : QObject() {} // disabled
};






class EvaluatorThread : public QThread {

    Q_OBJECT

public:
    EvaluatorThread(QObject* parent = NULL) : QThread(parent) {}
    virtual ~EvaluatorThread() {
        delete eval;
    }

    virtual void run() {
        eval = new Evaluator(NULL);
        emit ready();
        exec();
    }

    virtual Evaluator* getEvaluator() { return eval; }

signals:
    void ready();

protected:
    Evaluator* eval;

};

#endif	/* _EVALUATOR_H */

