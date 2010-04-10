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

    virtual void dispatchAndDeletePacket(Packet* packet);

    virtual void dumpSendersAndReceivers();

    // owner! this is a separate model because of sync problems (one frame ahead) and thread safety
    Model* model;

    // TODO implement priority-queue by timecode

    QVector<Receiver*> receivers;
    QVector<Sender*> senders;

    int readyCnt;

    QTimer timer;

private:
    Evaluator(const Evaluator& orig) {} // disabled
};

#endif	/* _EVALUATOR_H */

