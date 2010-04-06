/* 
 * File:   View.cpp
 * Author: pavel
 * 
 * Created on 5. duben 2010, 10:51
 */

#include "View.h"

#include <QPalette>

View::View(QWidget* parent, Model* _model) : QWidget(parent), model(_model) {
    tunnel.setColor(Qt::black);
    tile = QPixmap::fromImage(QImage("tile.png"));
    x = y = 0;
}

View::~View() {
}

void View::paintEvent(QPaintEvent* /*evt*/) {

    int wid = width();
    int hei = height();

    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    painter.drawTiledPixmap(0,0,width(),height(),tile, x % tile.width(), y % tile.height());

    const uchar* data = model->getTunnelBitmapData(0,0,wid,hei);
    tunnel.setTexture(QBitmap::fromData(QSize(wid,hei),data,QImage::Format_MonoLSB));
    delete data;

    painter.setBrush(tunnel);
    painter.drawRect(0,0,wid-1,hei-1);

    //TODO draw BitmapObjects
    QVector<BitmapObj*> bitmaps = model->getBitmapsInRect(x,y,wid,hei);
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
