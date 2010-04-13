/*
 *      -----------------------------------------------
 *      QTunneler - a classic DOS game remake in QT
 *      -----------------------------------------------
 *
 *      semestral project for API programming course
 *      (Y36API) at the FEE CTU Prague
 *
 *      Created by:
 *           Pavel Sramek (sramepa1@fel.cvut.cz)
 *           Martin Smarda (smardmar@fel.cvut.cz)
 *
 *      March & April 2010
 *
 *      This is free software, licensed under GNU LGPL
 *      (GNU Lesser General Public License, version 3)
 *      http://www.gnu.org/licenses/lgpl.html
 *
 *      Project homepage:
 *      http://code.google.com/p/qtunneler/
 *
 *      Version 1.0
 *
 */

#ifndef _PACKET_H
#define	_PACKET_H

#include <QtCore>

class Packet {
public:
    Packet(quint32 op =0, quint32 time =0, quint32 d1 =0, quint32 d2 =0, quint32 d3 =0)
        : opcode(op), timecode(time), data1(d1), data2(d2), data3(d3) {}
        
    virtual ~Packet() {}

    // use default copy constructor

    quint32 opcode;

    quint32 timecode;

    quint32 data1; // ID
    quint32 data2; // X
    quint32 data3; // Y

    
};

#endif	/* _PACKET_H */

