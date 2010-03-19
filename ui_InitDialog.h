/********************************************************************************
** Form generated from reading ui file 'InitDialog.ui'
**
** Created: Fri Mar 19 12:29:11 2010
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INITDIALOG_H
#define UI_INITDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_InitDialog
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *InitDialog)
    {
        if (InitDialog->objectName().isEmpty())
            InitDialog->setObjectName(QString::fromUtf8("InitDialog"));
        InitDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(InitDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        retranslateUi(InitDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), InitDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), InitDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(InitDialog);
    } // setupUi

    void retranslateUi(QDialog *InitDialog)
    {
        InitDialog->setWindowTitle(QApplication::translate("InitDialog", "InitDialog", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(InitDialog);
    } // retranslateUi

};

namespace Ui {
    class InitDialog: public Ui_InitDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITDIALOG_H
