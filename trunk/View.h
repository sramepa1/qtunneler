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

#ifndef _VIEW_H
#define	_VIEW_H

#include <QPainter>
#include <QWidget>
#include <QEvent>
#include <QBitmap>
#include <QHash>

#include "Model.h"
#include "BitmapObj.h"
#include "Clicker.h"
#include "DefaultValues.h"

class View : public QWidget {

    Q_OBJECT

public:
    View(QWidget* parent = NULL, Model* _model = NULL, Clicker* _clicker = NULL);
    virtual ~View();

    virtual void setViewpoint(qint32 x, qint32 y);

protected:
    void paintEvent(QPaintEvent* evt);

    void keyPressEvent(QKeyEvent* evt);
    void keyReleaseEvent(QKeyEvent* evt);

    qint32 x;
    qint32 y;

    QPen tunnel;
    QPen solid;
    QBrush border;
    QBrush shot;
    QBrush white;
    
    QPixmap tile;

    QHash< qint32, QHash<qint32,QPixmap> > tanks;

    //not owner
    Model* model;
    Clicker* clicker;
};

#endif	/* _VIEW_H */

