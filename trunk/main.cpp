/*
 * File:   main.cpp
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:15
 */

#include <QtGui/QApplication>
#include <qt4/QtGui/qwidget.h>

#include "InitDialog.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    InitDialog* dialog = new InitDialog();
    dialog->show();
    // create and show your widgets here

    return app.exec();
}