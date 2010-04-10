/* 
 * File:   Evaluator.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:42
 */

#include "Evaluator.h"

Evaluator::Evaluator(QObject* parent) : QThread(parent) {
    model = new Model(this);
}

Evaluator::~Evaluator() {
    dumpSendersAndReceivers();
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
}

void Evaluator::clearStateAndStop() {
    dumpSendersAndReceivers();
    quit();
}

void Evaluator::dumpSendersAndReceivers() {
    foreach(Sender* s,senders) {
        delete s;
    }
    senders.clear();
    foreach(Receiver* r,receivers) {
        delete r;
    }
    receivers.clear();
}

void Evaluator::generateWorldAndStartRound() {

    // TODO generate everything here

    dispatchAndDeletePacket(new Packet(OP_INIT_START));

    // TODO send everything here

    // TODO Tanks - bypass regular dispatcher - first tank sent = player tank
    // then just send all tanks everywhere, duplication does not matter

    dispatchAndDeletePacket(new Packet(OP_INIT_END));

    //TODO wait for confirmations

    dispatchAndDeletePacket(new Packet(OP_START_GAME));
}