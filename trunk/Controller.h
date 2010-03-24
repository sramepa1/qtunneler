/* 
 * File:   Controller.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:42
 */

#ifndef _CONTROLLER_H
#define	_CONTROLLER_H

class Controller {
public:
    Controller();
    virtual ~Controller();

private:    
    Controller(const Controller& orig) {} // disabled
};

#endif	/* _CONTROLLER_H */

