/* 
 * File:   Receiver.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:44
 */

#ifndef _RECEIVER_H
#define	_RECEIVER_H

class Receiver {
public:
    Receiver();
    virtual ~Receiver();

private:
    QueueSender(const QueueSender& orig) {} // disabled
};

#endif	/* _RECEIVER_H */

