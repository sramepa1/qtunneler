/* 
 * File:   Evaluator.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:42
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
    Evaluator(QObject* parent = NULL, Model* _model = NULL);
    virtual ~Evaluator();

    virtual void run();

    virtual void addSender(Sender* s);
    virtual void addReceiver(Receiver* r);

    // clear model, generate all world data AND send to all clients via packet dispatch
    // when world confirmed by all clients, dispatches start packets and enters evaluation/dispatch state machine
    virtual void generateWorldAndStartRound();
    
public slots:

    // Stop thread, dump queue contents, timer, senders and receivers
    virtual void clearStateAndStop();

signals:


protected:

    virtual void dispatchAndDeletePacket(Packet* packet);

    virtual void dumpSendersAndReceivers();

    // state machine: evaluation & dispatch vs. receive & wait
    bool evaluating;

    // not owner!
    Model* model;

    PacketQueue queue;

    QVector<Receiver*> receivers;
    QVector<Sender*> senders;

    QTimer timer;

private:
    Evaluator(const Evaluator& orig) {} // disabled
};

#endif	/* _EVALUATOR_H */

