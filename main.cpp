/*
 * File:   main.cpp
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:15
 */

#include <QApplication>

#include "Initializer.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
    
    Initializer init;
    init.initGUI();

    return app.exec();
}
