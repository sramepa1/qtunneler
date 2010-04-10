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

class Controller : public QThread {

    Q_OBJECT

public:
    Controller(QObject* parent = NULL, Model* _model = NULL);
    virtual ~Controller();

    virtual void run();

    virtual void resetStateAndStop();

    virtual void setReceiver(Receiver* r);

public slots:

signals:

    void initInProgress();
    void gameStarts();

    void redraw(quint32 x, quint32 y);

    void status(QString status);

    void endGame(QString message, bool ok);

protected:

    Receiver* receiver;

    Model* model;

private:    
    Controller(const Controller& orig) {} // disabled
};

#endif	/* _CONTROLLER_H */


