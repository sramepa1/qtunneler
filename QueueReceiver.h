/* 
 * File:   QueueReceiver.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:45
 */

#ifndef _QUEUERECEIVER_H
#define	_QUEUERECEIVER_H

#include "Receiver.h"

class QueueReceiver : public Receiver {
public:
    QueueReceiver();
    virtual ~QueueReceiver();

private:
    QueueReceiver(const QueueReceiver& orig) {} // disabled
};

#endif	/* _QUEUERECEIVER_H */

