/* 
 * File:   Dispatcher.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:43
 */

#ifndef _DISPATCHER_H
#define	_DISPATCHER_H

class Dispatcher {
public:
    Dispatcher();
    virtual ~Dispatcher();

private:
    
    Dispatcher(const Dispatcher& orig);
};

#endif	/* _DISPATCHER_H */

