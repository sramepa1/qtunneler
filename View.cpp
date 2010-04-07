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
    stone.setColor(Qt::gray);
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

    // draw background
    painter.drawTiledPixmap(0,0,width(),height(),tile, x % tile.width(), y % tile.height());

    // draw tunnel network
    const uchar* data = model->getTunnelBitmapData(0,0,wid,hei);
    tunnel.setTexture(QBitmap::fromData(QSize(wid,hei),data,QImage::Format_MonoLSB));
    delete data;
    painter.setBrush(tunnel);
    painter.drawRect(0,0,wid-1,hei-1);

    // draw bitmap objects
    painter.setBrush(stone);
    QVector<BitmapObj*> bitmaps = model->getSolidObjInRect(x,y,wid,hei);
    foreach(BitmapObj* bmp, bitmaps) {
        stone.setColor(bmp->getColor());
        stone.setTexture(*(bmp->getQBitmap()));
        painter.drawRect(bmp->getWrapperX1() - x, bmp->getWrapperY1() - y, bmp->getWrapperWidth(), bmp->getWrapperHeight());
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
