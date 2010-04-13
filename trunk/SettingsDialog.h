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

#ifndef _SETTINGSDIALOG_H
#define	_SETTINGSDIALOG_H

#include <QObject>
#include <QtGui>

#include "SettingsModel.h"

class SettingsDialog : public QWidget {

    Q_OBJECT

public:
    SettingsDialog(SettingsModel* _model);
    virtual ~SettingsDialog();

public slots:
    virtual void showSettings();
    virtual void hideSettingsAndSwitch();

    virtual void cancelClicked();
    virtual void createClicked();

    virtual void reload();

signals:
    void disconnect();
    void startGame();

    /* QTunneler 2.0
     *
    void nameChanged(QString newName);
    void colorChanged(quint8 newColor);
    void teamChanged(quint8 newTeam);
     *
    */

protected:
    SettingsModel* model;

    QLabel* statusLabel;

    QDialogButtonBox* buttonBox;
    QPushButton* startButton;
    
};

#endif	/* _SETTINGSDIALOG_H */

