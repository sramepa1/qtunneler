/* 
 * File:   Clicker.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:43
 */

#ifndef _CLICKER_H
#define	_CLICKER_H

#include "Sender.h"

class Clicker {
public:
    Clicker(Sender* s);
    virtual ~Clicker();

protected:

    Sender* sender;

private:    
    Clicker(const Clicker& orig) {} // disabled
};

#endif	/* _CLICKER_H */

