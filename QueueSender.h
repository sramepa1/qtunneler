/* 
 * File:   QueueSender.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:47
 */

#ifndef _QUEUESENDER_H
#define	_QUEUESENDER_H

#include "Sender.h"

class QueueSender : public Sender {
public:
    QueueSender();
    virtual ~QueueSender();

private:
    QueueSender(const QueueSender& orig) {} // disabled
};

#endif	/* _QUEUESENDER_H */

