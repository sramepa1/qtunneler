/* 
 * File:   InitDialog.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 12:26
 */

#ifndef _INITDIALOG_H
#define	_INITDIALOG_H

#include <QObject>
#include <QtGui>

#include "GameWindow.h"
#include "InitVector.h"
#include "Validator.h"

class InitDialog : public QWidget {
    Q_OBJECT

public:
    InitDialog(GameWindow* _gameWindow, Validator* _validator);
    virtual ~InitDialog();

public slots:
    void buttonClicked();
    void validated(QString message);

signals:
    void dialogOK(InitVector vec);

private:

    QRadioButton* createRadio;
    QRadioButton* joinRadio;

    QLabel* hostLabel;
    QLabel* portLabel;

    QLineEdit* hostField;
    QLineEdit* portField;

    QDialogButtonBox* buttonBox;


    GameWindow* gameWindow;
    Validator* validator;
};

#endif	/* _INITDIALOG_H */
