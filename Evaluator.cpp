/* 
 * File:   Evaluator.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:42
 */

#include "Evaluator.h"

Evaluator::Evaluator(QObject* parent, Model* _model) : QThread(parent) {
    model = _model;
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
    //TODO
}