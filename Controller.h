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
#include "View.h"

class Controller : public QThread {

    Q_OBJECT

public:
    Controller(Receiver* _receiver, Model* _model, View* _view);
    virtual ~Controller();

public slots:

signals:

protected:

    Receiver* receiver;

    Model* model;
    View* view;

private:    
    Controller(const Controller& orig) {} // disabled
};

#endif	/* _CONTROLLER_H */


