/*
 *      -----------------------------------------------
 *      QTunneler - a classic DOS game remake in QT
 *      -----------------------------------------------
 *
 *      semestral project for API programming course
 *      (Y36API) at the FEE CTU Prague
 *
 *      Created by:
 *           Pavel Sramek (sramepa1@fel.cvut.cz)
 *           Martin Smarda (smardmar@fel.cvut.cz)
 *
 *      March & April 2010
 *
 *      This is free software, licensed under GNU LGPL
 *      (GNU Lesser General Public License, version 3)
 *      http://www.gnu.org/licenses/lgpl.html
 *
 *      Project homepage:
 *      http://code.google.com/p/qtunneler/
 *
 *      Version 1.0
 *
 */

#include <QApplication>
#include <QThread>

#ifdef portaudio
#include <portaudio.h>
#endif

#include "Initializer.h"

int main(int argc, char *argv[]) {

#ifdef portaudio
    Pa_Initialize();
#endif

    QApplication app(argc, argv);
    
    Initializer init;
    init.startThreads();

    Waiter* w = new Waiter(&init,&app);
    w->start();

    int returnCode = app.exec();

#ifdef portaudio
    Pa_Terminate();
#endif

    delete w;

    return returnCode;
}
