/* 
 * File:   Dispatcher.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:43
 */

#ifndef _DISPATCHER_H
#define	_DISPATCHER_H

#include <QtCore>

#include "Sender.h"
#include "PacketQueue.h"

class Dispatcher {
public:
    Dispatcher();
    virtual ~Dispatcher();

    virtual void addSender(Sender* s);

    PacketQueue queue; // Shared with Evaluator

protected:

    QVector<Sender*> senders;

private:    
    Dispatcher(const Dispatcher& orig) {} // disabled
};

#endif	/* _DISPATCHER_H */

