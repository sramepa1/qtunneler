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

public slots:

    // clear model, generate all world data AND send to all clients via packet dispatch
    virtual void generateWorld();

signals:
    // emitted when world is ready and confirmed by clients
    void worldReady();


protected:

    virtual void dispatchAndDeletePacket(Packet* packet);

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

