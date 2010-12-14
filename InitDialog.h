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
#ifndef _INITDIALOG_H
#define	_INITDIALOG_H

#include <QObject>
#include <QString>
#include <QtGui>

#include "GameWindow.h"
#include "InitVector.h"

/**
 * Class of the dialog window where the players set parameters of the LAN
 * connection.
 */
class InitDialog : public QWidget {

    Q_OBJECT

public:
    InitDialog();
    virtual ~InitDialog();

public slots:
    virtual void buttonClicked();
    virtual void validated(QString message);

    virtual void createSelected();
    virtual void joinSelected();

    virtual void showDialog();

signals:
    void validateDialog(InitVector vec);
    void switchToSettings();

protected:

    virtual QString getIP();

    QRadioButton* createRadio;
    QRadioButton* joinRadio;

    QLabel* hostLabel;
    QLabel* portLabel;

    QLineEdit* hostField;
    QLineEdit* portField;

    QLabel* statusLabel;
    QDialogButtonBox* buttonBox;

};

#endif	/* _INITDIALOG_H */
