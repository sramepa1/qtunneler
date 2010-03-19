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
    QueueReceiver(const QueueReceiver& orig);
    virtual ~QueueReceiver();
private:

};

#endif	/* _QUEUERECEIVER_H */

