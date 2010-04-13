/*
 *      -----------------------------------------------
 *      QTunneler - a classic DOS game remake in QT
 *      -----------------------------------------------
 *
 *      semestral project for API programming course
 *      (Y36API) at the FEE CTU Prague
 *
 *      Created by:
 *           Pavel Sramek (sramepa1@fel.cvut.cz)
 *           Martin Smarda (smardmar@fel.cvut.cz)
 *
 *      March & April 2010
 *
 *      This is free software, licensed under GNU LGPL
 *      (GNU Lesser General Public License, version 3)
 *      http://www.gnu.org/licenses/lgpl.html
 *
 *      Project homepage:
 *      http://code.google.com/p/qtunneler/
 *
 *      Version 1.0
 *
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

   //delete
   // virtual void init();
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
    virtual bool isTankCollision (const Projectile * projectile) const;
    virtual bool isProjectileCollision (const RoundObj * projectile) const;
    virtual bool isCollisionForTank (const Tank * obj) const;
    virtual bool isCollisionForProjectile (const Projectile * projectile) const;

    /**
     * Explosion methods
     */

    /**
     * Tank control methods
     */

    virtual void moveTanksBackToBases();
    virtual void moveTankWhilePossible(Tank* tank);
    virtual qint32 getPixelCountInCircle(const RoundObj * obj);

    /**
     * Costruction methods
     */

    virtual void addBase(qint32 _x, qint32 _y, qint32 _width, qint32 _height, quint8 _color, QColor _wallColor);

    /**
     * Static methods
     */

    static bool checkRectOverlap(qint32 x11, qint32 y11, qint32 x12, qint32 y12, qint32 x21, qint32 y21, qint32 x22, qint32 y22);
    static bool checkRectInsideRect(qint32 x11, qint32 y11, qint32 x12, qint32 y12, qint32 x21, qint32 y21, qint32 x22, qint32 y22);

    // making these private or protected would result in a tremendous method count
    // better leave them public and open to Controller's logic

    Matrix* matrix;
    Border* border;
    
    QVector<Base*> * bases;
    QVector<BitmapObj*> * solidObjects; //stones and basewalls
    QVector<Explosion*> * explosions;

    QHash<qint32,Tank*> * tanks;
    QHash<qint32,Projectile*> * projectiles;

    QHash<qint32,QColor*> playerColors;
    qint32 playerID;

    // to synchronize access by view and controller
    QMutex containerAccess;

protected:
    quint32 nextProjectileID;

    void deleteObjectsInContainers();

private:
    Model(const Model& /*orig*/) : QObject() {} // disabled
};

#endif	/* _MODEL_H */

