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

class View : public QWidget {

    Q_OBJECT

public:
    View(QWidget* parent = NULL, Model* _model = NULL);
    virtual ~View();

protected:
    void paintEvent(QPaintEvent* evt);

    QBrush background;
    QBrush texture;

    QBitmap* bitmap;

    QPixmap tile;

    Model* model;
};

#endif	/* _VIEW_H */

