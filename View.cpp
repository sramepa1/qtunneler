/* 
 * File:   View.cpp
 * Author: pavel
 * 
 * Created on 5. duben 2010, 10:51
 */

#include "View.h"

#include <QPalette>


View::View(QWidget* parent, Model* _model) : QWidget(parent) {

    model = _model;

    setAutoFillBackground(true);

    background.setColor(Qt::black);
    background.setStyle(Qt::SolidPattern);

    QPalette p (palette());
    p.setColor(QPalette::Window,Qt::black);
    setPalette(p);

    //texture.setTexture()
}

View::~View() {
}

void View::paintEvent(QPaintEvent* /*evt*/) {
    QPainter painter(this);
    painter.setBackgroundMode(Qt::OpaqueMode);
    painter.setBackground(background);    
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(0,0,width()-1,height()-1);
}

