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

class InitDialog : public QWidget {
    Q_OBJECT

public:
    InitDialog();
    virtual ~InitDialog();

public slots:
    void buttonClicked();
    void validated(QString message);

    void createSelected();
    void joinSelected();

    void showDialog();

signals:
    void validateDialog(InitVector vec);
    void switchToWindow();

private:

    QRadioButton* createRadio;
    QRadioButton* joinRadio;

    QLabel* hostLabel;
    QLabel* portLabel;

    QLineEdit* hostField;
    QLineEdit* portField;

    QDialogButtonBox* buttonBox;

};

#endif	/* _INITDIALOG_H */
