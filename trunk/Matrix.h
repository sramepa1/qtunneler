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

#ifndef _MATRIX_H
#define	_MATRIX_H

#include "DefaultValues.h"
#include "BitmapObj.h"

/**
 * The class represents the undeground land-mass and the tunels in it.
 */
class Matrix {
public:
    Matrix();
    virtual ~Matrix();

    virtual bool getXY(qint32 x, qint32 y) const { return (arr[x/8][y]) & (1 << (x%8)); }
    virtual quint8 getByte(qint32 xDiv8, qint32 y) const { return arr[xDiv8][y]; }

    virtual void setXY(qint32 x, qint32 y, bool val) { arr[x/8][y] = val ? (arr[x/8][y] | (1 << (x%8))) : (arr[x/8][y] & ~(1 << (x%8))); }
    virtual void setByte(qint32 xDiv8, qint32 y, quint8 val) { arr[xDiv8][y] = val; }

    virtual void reset();

    //Print given mask to matrix. (and)
    virtual void maskMatrix(const BitmapObj * mask);
    //Print given mask to matrix. (and not)
    virtual void invertMaskMatrix(const BitmapObj * mask);

protected:
    quint8** arr;
    // 1 represents clue, 0 represents tunnel

private:
    Matrix(const Matrix& /*orig*/) {} // disabled
};

#endif	/* _MATRIX_H */

