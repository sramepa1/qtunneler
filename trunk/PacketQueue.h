/* 
 * File:   PacketQueue.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:43
 */

#ifndef _PACKETQUEUE_H
#define	_PACKETQUEUE_H

class PacketQueue {
public:
    PacketQueue();    
    virtual ~PacketQueue();
    
private:
    PacketQueue(const PacketQueue& orig) {} // disabled
};

#endif	/* _PACKETQUEUE_H */

