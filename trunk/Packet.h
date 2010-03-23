/* 
 * File:   Packet.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:43
 */

#ifndef _PACKET_H
#define	_PACKET_H

class Packet {
public:
    Packet();
    virtual ~Packet();

private:

    Packet(const Packet& orig);
};

#endif	/* _PACKET_H */

