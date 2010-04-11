/* 
 * File:   Clicker.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:43
 */

#include "Clicker.h"

Clicker::Clicker(QObject* parent, Model* _model) : QObject(parent), model(_model) {
    sender = NULL;
    up = down = left = right = 0;
    shoot = shootChanged = movementChanged = keyHeld = false;
    lastShootChange = lastMovementChange = 0;
    timer.start(FRAME_MSECS);
    connect(&timer,SIGNAL(timeout()),this,SLOT(sendState()));
}

Clicker::~Clicker() {
    if(sender != NULL) delete sender;
}

void Clicker::resetSender(Sender* s) {
    if(sender != NULL) delete sender;
    sender = s;
}

void Clicker::startClock() {
    time.setHMS(0,0,0,0);
    time.start();
}

void Clicker::confirmInitEnd() {
    sender->sendPacket(Packet(OP_INIT_CONFIRM));
}

bool Clicker::keyPressEvent(QKeyEvent* evt) {
    return handleKey(evt,1);
}

bool Clicker::keyReleaseEvent(QKeyEvent* evt) {
    return handleKey(evt,0);
}

bool Clicker::handleKey(QKeyEvent* evt, uchar val) {
    if(evt->isAutoRepeat()) {
        evt->ignore();
        return true;
    }
    switch(evt->key()) {
        case Qt::Key_Right : checkChanged(val, &right, &lastMovementChange, &movementChanged); return true;
        case Qt::Key_Left : checkChanged(val, &left, &lastMovementChange, &movementChanged); return true;
        case Qt::Key_Up : checkChanged(val, &up, &lastMovementChange, &movementChanged); return true;
        case Qt::Key_Down : checkChanged(val, &down, &lastMovementChange, &movementChanged); return true;
        case Qt::Key_Space : checkChanged(val, &shoot, &lastShootChange, &shootChanged); return true;
    }
    return false;
}

void Clicker::sendState() {
    bool tmp = keyHeld;
    keyHeld = true;
    while(!queue.isEmpty()) {
        MyEvt e = queue.dequeue();
        checkChanged(e.val,e.stored,e.timecode,e.flag);
    }
    keyHeld = tmp;
    if(shootChanged) {
        sender->sendPacket(Packet(OP_SHOOT, lastShootChange, model->getFirstTankID(), shoot ? 1 : 0, 0));
    }
    if(movementChanged) {
        int horizontal = right - left;
        int vertical = up - down;
        int direction;
        switch(vertical) {
            case -1:    switch(horizontal) {
                            case -1: direction = MOVE_SW; break;
                            case 0: direction = MOVE_S; break;
                            case 1: direction = MOVE_SE;
                        } break;

            case 0:     switch(horizontal) {
                            case -1: direction = MOVE_W; break;
                            case 0: direction = MOVE_STOP; break;
                            case 1: direction = MOVE_E;
                        } break;

            case 1:     switch(horizontal) {
                            case -1: direction = MOVE_NW; break;
                            case 0: direction = MOVE_N; break;
                            case 1: direction = MOVE_NE;
                        }
        }
        sender->sendPacket(Packet(OP_MOVE, lastMovementChange, model->getFirstTankID(), direction, 0));
    }

    if(shootChanged || movementChanged) sender->flush();

    keyHeld =  right != 0 || left != 0 || up != 0 || down != 0;

    shootChanged = movementChanged = false;
    timer.start(FRAME_MSECS);
}

void Clicker::checkChanged(uchar val, uchar* stored, int* timecode, bool* flag) {
    if(val != *stored) {
        if(val == 0 && !keyHeld) {
            MyEvt e;
            e.val = val;
            e.stored = stored;
            e.timecode = timecode;
            e.flag = flag;
            queue.enqueue(e);
        }else {
            *stored = val;
            *timecode = time.elapsed();
            *flag = true;
        }
    }
}
