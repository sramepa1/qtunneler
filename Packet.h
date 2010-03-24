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
    Packet() : Packet(0,0,0,0,0) {}
    Packet(quint32 op, quint32 time, quint32 d1, quint32 d2, quint32 d3)
        : opcode(op), timecode(time), data1(d1), data2(d2), data3(d3) {}

    virtual ~Packet();

    // use default copy constructor

    quint32 opcode;

    quint32 timecode;

    quint32 data1; // ID
    quint32 data2; // X
    quint32 data3; // Y

    
};

#endif	/* _PACKET_H */

