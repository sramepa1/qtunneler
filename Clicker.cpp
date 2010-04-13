/*
 *      -----------------------------------------------
 *      QTunneler - a classic DOS game remake in QT
 *      -----------------------------------------------
 *
 *      semestral project for API programming course
 *      (Y36API) at the FEE CTU Prague
 *
 *      Created by:
 *           Pavel Sramek (sramepa1@fel.cvut.cz)
 *           Martin Smarda (smardmar@fel.cvut.cz)
 *
 *      March & April 2010
 *
 *      This is free software, licensed under GNU LGPL
 *      (GNU Lesser General Public License, version 3)
 *      http://www.gnu.org/licenses/lgpl.html
 *
 *      Project homepage:
 *      http://code.google.com/p/qtunneler/
 *
 *      Version 1.0
 *
 */

#include "Clicker.h"

Clicker::Clicker(QObject* parent, Model* _model) : QObject(parent), model(_model) {
    sender = NULL;
    up = down = left = right = 0;
    shoot = false;
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
        case Qt::Key_Right : handleChange(val, &right); return true;
        case Qt::Key_Left : handleChange(val, &left); return true;
        case Qt::Key_Up : handleChange(val, &up); return true;
        case Qt::Key_Down : handleChange(val, &down); return true;
        case Qt::Key_Control : handleChange(val, &shoot); return true;
    }
    return false;
}

void Clicker::handleChange(uchar val, uchar* stored) {

    *stored = val;

    if(stored == &shoot) {
        sender->sendPacket(Packet(OP_SHOOT, time.elapsed(), model->playerID, shoot ? 1 : 0, 0));
        
    }else {
        int vertical = up - down;
        int horizontal = right - left;
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
        sender->sendPacket(Packet(OP_MOVE, time.elapsed(), model->playerID, direction, 0));
    }
    sender->flush();
}
