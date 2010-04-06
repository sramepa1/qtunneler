/* 
 * File:   Controller.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:42
 */

#include "Controller.h"

Controller::Controller(Receiver* _receiver, Model* _model, View* _view) {
    receiver = _receiver;
    model = _model;
    view = _view;
}

Controller::~Controller() {
}

