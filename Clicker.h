/* 
 * File:   Clicker.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:43
 */

#ifndef _CLICKER_H
#define	_CLICKER_H

#include <QObject>
#include <QTime>
#include <QKeyEvent>

#include "Sender.h"
#include "DefaultValues.h"
#include "Model.h"

class Clicker : public QObject {

    Q_OBJECT

public:
    Clicker(QObject* parent = NULL, Model* _model = NULL);
    virtual ~Clicker();

    virtual void resetSender(Sender* s);

    // returns true when handled, false when not interested
    virtual bool keyPressEvent(QKeyEvent* evt);
    virtual bool keyReleaseEvent(QKeyEvent* evt);

public slots:

    // use sender to send confirmation packet
    virtual void confirmInitEnd();

    virtual void startClock();

protected:

    virtual void handleChange(uchar val, uchar* stored);

    virtual bool handleKey(QKeyEvent* evt, uchar val);

    uchar up;
    uchar down;
    uchar left;
    uchar right;

    uchar shoot;

    Sender* sender;
    QTime time;

    //not owner
    Model* model;

private:    
    Clicker(const Clicker& orig) {} // disabled
};

#endif	/* _CLICKER_H */

