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

    virtual void init();
    virtual void reset();

    /**
     * Data for transforming Matrix to QBitmap
     */
    virtual const uchar* getTunnelBitmapData(qint32 x, qint32 y, qint32 width, qint32 height) const;


    virtual QVector<BitmapObj*> getSolidObjInRect(qint32 x, qint32 y, qint32 width, qint32 height) const;

    virtual QVector<QPoint> getShotsInRect(qint32 x, qint32 y, qint32 width, qint32 height) const;

    /**
     * Collision detection;
     */

    bool isMatrixCollision (const RoundObj * obj) const;

    //Collision with stone, basewall or border.
    bool isSolidCollision (const RoundObj * obj) const;
    bool isTankCollision (const RoundObj * obj) const;
    bool isProjectileCollision (const RoundObj * obj) const;
    bool isAnyCollision (const RoundObj * obj) const;

    /**
     * Explosion methods
     */

    //Create exlosion, burn clue in matrix, damage tanks and destroye all projectiles within explosion radius
    void projectileExplosion(qint32 shotID);

    /**
     * Tank control methods
     */
    
    void tankFire(qint32 tankID);

    /**
     * Static methods
     */

    static bool checkRectOverlap(qint32 x11, qint32 y11, qint32 x12, qint32 y12, qint32 x21, qint32 y21, qint32 x22, qint32 y22);

    // making these private or protected would result in a tremendous method count
    // better leave them public and open to Controller's logic

    Matrix* matrix;
    Border* border;
    
    QVector<Base*> * bases;
    QVector<BitmapObj*> * solidObjects; //stones and basewalls
    QVector<Explosion*> * explosions; //TODO sebrat id

    QHash<qint32,Tank*> * tanks;
    QHash<qint32,Projectile*> * projectiles;
private:
    Model(const Model& orig) {} // disabled
};

#endif	/* _MODEL_H */

