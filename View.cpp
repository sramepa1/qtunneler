/* 
 * File:   View.cpp
 * Author: pavel
 * 
 * Created on 5. duben 2010, 10:51
 */

#include "View.h"

#include <QPalette>

#include <iostream>

View::View(QWidget* parent, Model* _model) : QWidget(parent), model(_model) {
    tunnel.setColor(Qt::black);
    tile = QPixmap::fromImage(QImage("dirt_small.png"));
    x = y = 0;
}

View::~View() {
}

void View::paintEvent(QPaintEvent* /*evt*/) {

    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    painter.drawTiledPixmap(0,0,width(),height(),tile, x % tile.width(), y % tile.height());

    const uchar* data = model->getTunnelBitmapData(0,0,width(),height());
    tunnel.setTexture(QBitmap::fromData(QSize(width(),height()),data,QImage::Format_MonoLSB));
    delete data;

    painter.setBrush(tunnel);
    painter.drawRect(0,0,width()-1,height()-1);

    //TODO draw BitmapObjects
    QVector<BitmapObj*> bitmaps = model->getBitmapsInRect(x,y,width(),height());
    for (int i = 0; i < bitmaps.size(); i++) {
        paintBitmap(painter, bitmaps[i]);
    }


    //TODO draw RoundObjects
}

QPoint View::getViewpoint() {
    return QPoint(x,y);
}


void View::setViewpoint(quint32 _x, quint32 _y) {
    x = _x;
    y = _y;
}

void View::paintBitmap(QPainter& painter, BitmapObj* obj) {

    //TODO

}
