/* 
 * File:   Evaluator.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:42
 */

#ifndef _EVALUATOR_H
#define	_EVALUATOR_H

#include <QtCore>

#include "PacketQueue.h"
#include "Receiver.h"

class Evaluator {
public:
    Evaluator();    
    virtual ~Evaluator();

protected:

    bool evaluating;

    PacketQueue queue;

    QVector<Receiver*> receivers;

private:
    Evaluator(const Evaluator& orig) {} // disabled
};

#endif	/* _EVALUATOR_H */

