/* 
 * File:   Controller.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:42
 */

#ifndef _CONTROLLER_H
#define	_CONTROLLER_H

#include <QtCore>
#include "Receiver.h"
#include "Model.h"

class Controller {
public:
    Controller(Receiver* rec);
    virtual ~Controller();

    // TODO methods

protected:

    Receiver* receiver;

    Model model;

private:    
    Controller(const Controller& orig) {} // disabled
};

#endif	/* _CONTROLLER_H */


