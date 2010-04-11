/* 
 * File:   Controller.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:42
 */

#include "Controller.h"

Controller::Controller(QObject* parent, Model* _model) : QThread(parent) {
    receiver = NULL;
    model = _model;
}

Controller::~Controller() {
    quit();
    while(isRunning()) {}
}

void Controller::run() {
    exec();
}

void Controller::resetStateAndStop() {
    model->reset();
    quit();
}

void Controller::setReceiver(Receiver* r) {
    if(receiver != NULL) {
        disconnect(receiver,0,0,0);
        delete receiver;
    }
    receiver = r;
    connect(receiver,SIGNAL(packetReady(Receiver*)),this,SLOT(handlePacket(Receiver*)));
}

void Controller::handlePacket(Receiver* /*r*/) {

    //qDebug("controller got packet");
    // TODO implement main packet-switch code here!

    Packet pack = receiver->getPacket();

    switch(pack.opcode) {
        case OP_INIT_START: emit initInProgress(); break;
        case OP_INIT_END: emit confirmInitEnd(); break;
        case OP_START_GAME: emit gameStarts(); break;

        case 424242: emit redrawToCenter(pack.data1,pack.data2);
    }

}

