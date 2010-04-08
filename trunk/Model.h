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
#include "Explosion.h"
#include "Tank.h"
#include "Projectile.h"

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

    static bool isMatrixCollision (const RoundObj obj);

    /**
     * Collision with stone, basewall or border.
     */
    static bool isSolidCollision (const RoundObj obj);

    static bool isTankCollision (const RoundObj obj);
    static bool isAnyCollision (const RoundObj obj);

    // making these private or protected would result in a tremendous method count
    // better leave them public and open to Controller's logic

    Matrix* matrix;
    Border* border;
    
    QVector<Base*> * bases;
    QVector<BitmapObj*> * solidObjects; //stones and basewalls

    QHash<quint32,Tank*> * tanks;
    QHash<quint32,Projectile*> * projectiles;
    QHash<quint32,Explosion*> * explosions;

private:
    Model(const Model& orig) {} // disabled
};

#endif	/* _MODEL_H */

