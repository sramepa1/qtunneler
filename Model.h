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
#include "Stone.h"

class Model : public QObject {

    Q_OBJECT

public:
    Model(QObject* _parent = NULL);
    virtual ~Model();

    virtual void init();
    virtual void reset();

    /**
     * Data for transforming Matrix to QBitmap
     */
    virtual const uchar* getTunnelBitmapData(qint32 x, qint32 y, qint32 width, qint32 height) const;

    /**
     * Object drawing
     */
    virtual QVector<BitmapObj*> getSolidObjInRect(qint32 x, qint32 y, qint32 width, qint32 height) const;
    virtual QVector<QRect> getBorderInRect(qint32 x, qint32 y, qint32 width, qint32 height) const;
    virtual QVector<QPoint> getShotsInRect(qint32 x, qint32 y, qint32 width, qint32 height) const;
    virtual QVector<OrientedRoundObj*> getTanksInRect(qint32 x, qint32 y, qint32 width, qint32 height) const;

    virtual quint32 provideProjectileID() { return nextProjectileID++;}

    
    virtual void maskMatrixWithTank(qint32 tankID, qint32 newX, qint32 newY);

    /**
     * Collision detection;
     */

    virtual bool isMatrixCollision (const RoundObj * obj) const;

    //Collision with stone, basewall or border.
    virtual bool isSolidCollision (const RoundObj * obj) const;
    virtual bool isTankCollision (const RoundObj * obj) const;
    virtual bool isProjectileCollision (const RoundObj * obj) const;
    virtual bool isAnyCollision (const RoundObj * obj) const;

    /**
     * Explosion methods
     */

    // TODO rewrite
    //Create exlposion, burn clue in matrix, damage tanks and destroye all projectiles within explosion radius
    virtual void projectileExplosion(qint32 projectileID, qint32 x, qint32 y, qint32 srand);

    /**
     * Tank control methods
     */
    
    virtual void tankFire(qint32 tankID);
    virtual qint32 getPixelCountInCircle(const RoundObj * obj);

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
    QVector<Explosion*> * explosions;

    QHash<qint32,Tank*> * tanks;
    QHash<qint32,Projectile*> * projectiles;

    qint32 playerID;

    // to synchronize access by view and controller
    QMutex containerAccess;

protected:
    quint32 nextProjectileID;

    void cleanContainers();

private:
    Model(const Model& orig) {} // disabled
};

#endif	/* _MODEL_H */

