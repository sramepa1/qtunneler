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

#include "Model.h"
#include "BitmapObj.h"
#include "DefaultValues.h"

class View : public QWidget {

    Q_OBJECT

public:
    View(QWidget* parent = NULL, Model* _model = NULL);
    virtual ~View();

    virtual void setViewpoint(qint32 x, qint32 y);

protected:
    void paintEvent(QPaintEvent* evt);

    qint32 x;
    qint32 y;

    QBrush tunnel;
    QBrush solid;
    QBrush shot;

    QBitmap* bitmap;

    QPixmap tile;

    Model* model;
};

#endif	/* _VIEW_H */

