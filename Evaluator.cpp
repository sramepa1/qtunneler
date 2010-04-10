/* 
 * File:   Evaluator.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:42
 */

#include "Evaluator.h"

Evaluator::Evaluator(QObject* parent) : QThread(parent) {
    model = new Model(this);
    readyCnt = 0;
    connect(&timer,SIGNAL(timeout()),this,SLOT(evaluateState()));
}

Evaluator::~Evaluator() {
    dumpSendersAndReceivers();
    quit();
    while(isRunning()) {}
}

void Evaluator::run() {
    //enter event loop
    exec();
}

void Evaluator::dispatchAndDeletePacket(Packet* packet) {
    foreach(Sender* s, senders) s->sendPacket(*packet);
    delete packet;
}

void Evaluator::addSender(Sender* s) {
    senders.push_back(s);
}

void Evaluator::addReceiver(Receiver* r) {
    receivers.push_back(r);
    connect(r,SIGNAL(packetReady(Receiver*)),this,SLOT(handlePacket(Receiver*)));
}

void Evaluator::clearStateAndStop() {
    readyCnt = 0;
    timer.stop();
    dumpSendersAndReceivers();
    quit();
}

void Evaluator::dumpSendersAndReceivers() {
    foreach(Sender* s,senders) {
        delete s;
    }
    senders.clear();
    foreach(Receiver* r,receivers) {
        disconnect(r,0,0,0);
        delete r;
    }
    receivers.clear();
}

void Evaluator::generateWorldAndStartRound() {

    // TODO generate everything here
    qDebug("evaluator - starting");
    dispatchAndDeletePacket(new Packet(OP_INIT_START));

    // TODO send everything here

    // TODO Tanks - bypass regular dispatcher - first tank sent = player tank
    // then just send all tanks everywhere, duplication does not matter

    dispatchAndDeletePacket(new Packet(OP_INIT_END));
    // will now wait for confirmations to arrive
}

void Evaluator::handlePacket(Receiver* r) {
    qDebug("evaluator got packet");
    Packet p = r->getPacket();
    if(p.opcode == OP_INIT_CONFIRM && ++readyCnt == receivers.size()) {
        qDebug("evaluator dispatching start packet");
        dispatchAndDeletePacket(new Packet(OP_START_GAME));
        timer.start(FRAME_MSECS);
    } else {

        // TODO add p to priority queue !!!

    }
}

void Evaluator::evaluateState() {

    // TODO main state-evaluation code here - go through queue, evaluate, dispatch packets
    timer.start(FRAME_MSECS);
}