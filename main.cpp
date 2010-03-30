/*
 * File:   main.cpp
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:15
 */

#include <QtGui/QApplication>

#include "InitDialog.h"
#include "GameWindow.h"
#include "Validator.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);
    
    GameWindow* g = new GameWindow();
    
    Validator* v = new Validator();

    InitDialog* dialog = new InitDialog(g,v);
    dialog->show();

    // create and show your widgets here

    return app.exec();
}
