/* 
 * File:   View.h
 * Author: pavel
 *
 * Created on 5. duben 2010, 10:51
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
    
    QPixmap tile;

    QHash< qint32, QHash<qint32,QPixmap> > tanks;

    //not owner
    Model* model;
    Clicker* clicker;
};

#endif	/* _VIEW_H */

