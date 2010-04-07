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

class View : public QWidget {

    Q_OBJECT

public:
    View(QObject* parent = NULL, Model* _model = NULL);
    virtual ~View();

    virtual void setViewpoint(quint32 x, quint32 y);
    virtual QPoint getViewpoint();

protected:
    void paintEvent(QPaintEvent* evt);

    void paintBitmap(QPainter& painter, BitmapObj* obj);

    quint32 x;
    quint32 y;

    QBrush tunnel;
    QBrush stone;

    QBitmap* bitmap;

    QPixmap tile;

    Model* model;
};

#endif	/* _VIEW_H */

