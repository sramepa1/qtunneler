/* 
 * File:   InitDialog.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 12:26
 */

#ifndef _INITDIALOG_H
#define	_INITDIALOG_H

#include <QObject>
#include <QString>
#include <QtGui>

#include "GameWindow.h"
#include "InitVector.h"

class InitDialog : public QWidget {

    Q_OBJECT

public:
    InitDialog(QObject* parent = NULL);
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
