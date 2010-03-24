/* 
 * File:   NetSender.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:47
 */

#ifndef _NETSENDER_H
#define	_NETSENDER_H

#include <QtNetwork>

#include "Sender.h"

class NetSender : public Sender{
public:
    NetSender();    
    virtual ~NetSender();

private:
    NetSender(const NetSender& orig) {} // disabled
};

#endif	/* _NETSENDER_H */

