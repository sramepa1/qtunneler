/* 
 * File:   SettingsDialog.h
 * Author: pavel
 *
 * Created on 31. březen 2010, 12:19
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

