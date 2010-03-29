/********************************************************************************
** Form generated from reading ui file 'InitDialog.ui'
**
** Created: Mon Mar 29 12:19:28 2010
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INITDIALOG_H
#define UI_INITDIALOG_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InitDialog
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QRadioButton *createRadio;
    QRadioButton *joinRadio;
    QLabel *hostLabel;
    QLineEdit *hostField;
    QLabel *portLabel;
    QDialogButtonBox *buttonBox;
    QLineEdit *PortField;

    void setupUi(QDialog *InitDialog)
    {
        if (InitDialog->objectName().isEmpty())
            InitDialog->setObjectName(QString::fromUtf8("InitDialog"));
        InitDialog->resize(390, 168);
        formLayoutWidget = new QWidget(InitDialog);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 7, 371, 152));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        createRadio = new QRadioButton(formLayoutWidget);
        createRadio->setObjectName(QString::fromUtf8("createRadio"));
        createRadio->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        createRadio->setChecked(true);

        formLayout->setWidget(0, QFormLayout::LabelRole, createRadio);

        joinRadio = new QRadioButton(formLayoutWidget);
        joinRadio->setObjectName(QString::fromUtf8("joinRadio"));
        joinRadio->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        formLayout->setWidget(1, QFormLayout::LabelRole, joinRadio);

        hostLabel = new QLabel(formLayoutWidget);
        hostLabel->setObjectName(QString::fromUtf8("hostLabel"));
        hostLabel->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        formLayout->setWidget(2, QFormLayout::LabelRole, hostLabel);

        hostField = new QLineEdit(formLayoutWidget);
        hostField->setObjectName(QString::fromUtf8("hostField"));
        hostField->setEnabled(false);
        hostField->setMaxLength(512);
        hostField->setReadOnly(false);

        formLayout->setWidget(2, QFormLayout::FieldRole, hostField);

        portLabel = new QLabel(formLayoutWidget);
        portLabel->setObjectName(QString::fromUtf8("portLabel"));
        portLabel->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        formLayout->setWidget(3, QFormLayout::LabelRole, portLabel);

        buttonBox = new QDialogButtonBox(formLayoutWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(4, QFormLayout::FieldRole, buttonBox);

        PortField = new QLineEdit(formLayoutWidget);
        PortField->setObjectName(QString::fromUtf8("PortField"));
        PortField->setEnabled(false);
        PortField->setMaxLength(5);
        PortField->setReadOnly(false);

        formLayout->setWidget(3, QFormLayout::FieldRole, PortField);


        retranslateUi(InitDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), InitDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), InitDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(InitDialog);
    } // setupUi

    void retranslateUi(QDialog *InitDialog)
    {
        InitDialog->setWindowTitle(QApplication::translate("InitDialog", "QTunneler", 0, QApplication::UnicodeUTF8));
        createRadio->setText(QApplication::translate("InitDialog", "Create game", 0, QApplication::UnicodeUTF8));
        joinRadio->setText(QApplication::translate("InitDialog", "Join game", 0, QApplication::UnicodeUTF8));
        hostLabel->setText(QApplication::translate("InitDialog", "Host:", 0, QApplication::UnicodeUTF8));
        portLabel->setText(QApplication::translate("InitDialog", "Port:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(InitDialog);
    } // retranslateUi

};

namespace Ui {
    class InitDialog: public Ui_InitDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITDIALOG_H
