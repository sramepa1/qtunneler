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

    // sends difference packets to evaluator
    virtual void sendState();

    // use sender to send confirmation packet
    virtual void confirmInitEnd();

    virtual void startClock();

protected:

    virtual void checkChanged(uchar val, uchar* stored, int* timecode, bool* flag);

    virtual bool handleKey(QKeyEvent* evt, uchar val);

    bool keyHeld;

    uchar up;
    uchar down;
    uchar left;
    uchar right;

    uchar shoot;

    bool movementChanged;
    int lastMovementChange;

    bool shootChanged;
    int lastShootChange;

    Sender* sender;
    QTime time;

    QTimer timer;

    struct MyEvt {
        uchar val;
        uchar* stored;
        int* timecode;
        bool* flag;
    };

    QQueue<MyEvt> queue;

    //not owner
    Model* model;

private:    
    Clicker(const Clicker& orig) {} // disabled
};

#endif	/* _CLICKER_H */

