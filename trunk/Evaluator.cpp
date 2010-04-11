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


    //TODO remove
    x = 512;
    y = 388;
    dx = dy = 0;
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

void Evaluator::dispatchPacket(Packet& packet) {
    foreach(Sender* s, senders) s->sendPacket(packet);
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
    
    Packet p(OP_INIT_START);
    dispatchPacket(p);
    
    // TODO send everything here

    // TODO Tanks - bypass regular dispatcher - first tank sent = player tank
    // then just send all tanks everywhere, duplication does not matter

    p = Packet(OP_INIT_END);
    dispatchPacket(p);
    // will now wait for confirmations to arrive
}

void Evaluator::handlePacket(Receiver* r) {
    //qDebug("evaluator got packet");
    Packet p = r->getPacket();

    // handle init confirmation
    if(p.opcode == OP_INIT_CONFIRM && ++readyCnt == receivers.size()) {
        //qDebug("evaluator dispatching start packet");
        Packet temp(OP_START_GAME);
        dispatchPacket(temp);
        timer.start(FRAME_MSECS);

    // add to priority queue
    } else if(list.isEmpty()) {
        list.append(p);
    } else {
        QLinkedList<Packet>::iterator i = list.end();
        while(--i != list.begin() && (*i).timecode >= p.timecode) {}
        
        if(i != list.begin() || (*i).timecode <= p.timecode) {
            ++i;
        }
        list.insert(i,p);
    }
}

void Evaluator::evaluateState() {
    // evaluate packets
    Packet temp;
    while(!list.isEmpty()) {
        
        Packet p = list.first();
        //qDebug("Evaluating %d, data1 %d, data2 %d",p.opcode,p.data1,p.data2);

        switch(p.opcode) {
            case OP_MOVE:  handleTankMovementChange(p.data1,p.data2); break;
            case OP_SHOOT:  handleTankShootChange(p.data1,p.data2);
        }

        list.removeFirst();
    }

    // TODO move all projectiles here (and handle any resulting collisions & generate explosions)

    // TODO execute all explosions - mask matrix, modify tank HPs

    // TODO check tank HPs for <= 0, remove tanks, generate any tankExplosions (and eval them, checking tank HP again)

    // TODO evaluate tank energy/HP gain from bases (distinguish own and emnemy)


    // TODO remove this - testing code
    x += dx;
    y += dy;

    Packet p(424242,0,x,y,0);
    updatePacket(p);
    // end of test


    //send changes
    foreach(Packet pack, tempList ) {
        dispatchPacket(pack);
        //qDebug("Dispatched opcode %d, data1 %d, data2 %d",pack.opcode,pack.data1,pack.data2);
    }
    tempList.clear();

    foreach(Sender* sender, senders) sender->flush();
    timer.start(FRAME_MSECS);
}

void Evaluator::updatePacket(Packet& p) {
    bool found = false;
    //qDebug("Updating %d, data1 %d, data2 %d",p.opcode,p.data1,p.data2);
    foreach(Packet pack, tempList) {
        if(pack.opcode == p.opcode) {
            //qDebug("Found it");
            found = true;
            pack = p;
        }
    }
    if(!found) {
        //qDebug("Not found, appending");
        tempList.append(p);
    }
}

void Evaluator::handleTankMovementChange(int tankID, int newDirection) {

    // TODO implement - check collisions, calculate energy cost, etc. then send (update) tank packet

    int step = 16;
    switch(newDirection) {
        case MOVE_STOP : dy = dx = 0; break;
        case MOVE_N : dy = -step; dx = 0; break;
        case MOVE_NE : dy = -step; dx = step; break;
        case MOVE_E : dy = 0; dx = step; break;
        case MOVE_SE : dy = dx = step; break;
        case MOVE_S : dy = step; dx = 0; break;
        case MOVE_SW : dy = step; dx = -step; break;
        case MOVE_W : dy = 0; dx = -step; break;
        case MOVE_NW : dy = dx = -step; break;
    }
}

void Evaluator::handleTankShootChange(int tankID, int newState) {

    // TODO implement

}