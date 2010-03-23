/* 
 * File:   Model.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:33
 */

#ifndef _MODEL_H
#define	_MODEL_H

#include <QtCore>

#include "Base.h"
#include "Border.h"
#include "Matrix.h"
#include "RoundObj.h"
#include "VectorObj.h"

class Model {
public:
    Model();    
    virtual ~Model();

    virtual void reset();

    Matrix matrix;
    Border* border;
    
    QVector<Base> bases;
    QVector<RoundObj> roundObjects;
    QVector<VectorObj> vecObjects;

private:

    Model(const Model& orig); //disabled
};

#endif	/* _MODEL_H */

