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

void Evaluator::generateWorld() {
    //TODO
}
