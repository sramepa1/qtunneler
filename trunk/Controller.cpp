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
}

void Controller::run() {
    exec();
}

void Controller::resetStateAndStop() {
    model->reset();
    quit();
}

void Controller::setReceiver(Receiver* r) {
    
}

