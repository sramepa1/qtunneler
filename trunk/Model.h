/* 
 * File:   Model.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:33
 */

#ifndef _MODEL_H
#define	_MODEL_H

#include <QtCore>
#include <QPoint>

#include "DefaultValues.h"

#include "Base.h"
#include "Border.h"
#include "Matrix.h"
#include "RoundObj.h"
#include "BitmapObj.h"

class Model : public QObject {

    Q_OBJECT

public:
    Model(QObject* parent = NULL);
    virtual ~Model();

    virtual void reset();


    /**
     * Data for transforming Matrix to QBitmap
     */
    virtual const uchar* getTunnelBitmapData(quint32 x, quint32 y, quint32 width, quint32 height) const;


    virtual QVector<BitmapObj*> getSolidObjInRect(quint32 x, quint32 y, quint32 width, quint32 height) const;

    virtual QVector<QPoint> getShotsInRect(quint32 x, quint32 y, quint32 width, quint32 height) const;

    // making these private or protected would result in a tremendous method count
    // better leave them public and open to Controller's logic

    Matrix* matrix;
    Border* border;
    
    QVector<Base*> * bases;
    QVector<BitmapObj*> * solidObjects;

    QHash<quint32,RoundObj*> * tanks;
    QHash<quint32,RoundObj*> * projectiles;

    //TODO explosions - will be stored? I suggest not.

private:
    Model(const Model& orig) {} // disabled
};

#endif	/* _MODEL_H */

