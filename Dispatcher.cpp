/* 
 * File:   Dispatcher.cpp
 * Author: pavel
 * 
 * Created on 19. březen 2010, 11:43
 */

#include "Dispatcher.h"

Dispatcher::Dispatcher() {
}

Dispatcher::~Dispatcher() {
}

void Dispatcher::addSender(Sender* s) {
    senders.push_back(s);
}
