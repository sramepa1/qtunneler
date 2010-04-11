/*
 * File:   InitDialog.cpp
 * Author: pavel
 *
 * Created on 19. březen 2010, 12:26
 */

#include "InitDialog.h"

#include "DefaultValues.h"

#include <QtNetwork>
#include <iostream>

InitDialog::InitDialog() {

    setWindowTitle(APP_NAME_STRING);

    createRadio = new QRadioButton(tr("&Create game"),this);
    joinRadio = new QRadioButton(tr("&Join game"),this);
    hostLabel = new QLabel(tr("host:"),this);
    portLabel = new QLabel(tr("port:"),this);
    hostField = new QLineEdit(this);
    portField = new QLineEdit(this);
    statusLabel = new QLabel("",this);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, Qt::Horizontal, this);

    hostLabel->setBuddy(hostField);
    portLabel->setBuddy(portField);

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(createRadio,0,0,1,3,Qt::AlignLeft);
    layout->addWidget(joinRadio,1,0,1,3,Qt::AlignLeft);
    layout->addWidget(hostLabel,2,0,1,1,Qt::AlignRight);
    layout->addWidget(hostField,2,1,1,2,Qt::AlignLeft);
    layout->addWidget(portLabel,3,0,1,1,Qt::AlignRight);
    layout->addWidget(portField,3,1,1,2,Qt::AlignLeft);
    layout->addWidget(statusLabel,4,0,1,2,Qt::AlignLeft);
    layout->addWidget(buttonBox,4,2,1,1,Qt::AlignRight);


    setLayout(layout);

    createRadio->setChecked(true);

    portField->setMaxLength(5);
    portField->setMinimumWidth(40);
    portField->setMaximumWidth(60);
    portField->setText("4242");

    hostField->setMaxLength(512);
    hostField->setMinimumWidth(256);
    hostField->setEnabled(false);
    hostField->setText(getIP());

    createRadio->show();
    joinRadio->show();
    hostLabel->show();
    hostField->show();
    portLabel->show();
    portField->show();
    statusLabel->show();
    buttonBox->show();

    connect(buttonBox,SIGNAL(accepted()),this,SLOT(buttonClicked()));

    connect(createRadio,SIGNAL(clicked()),this,SLOT(createSelected()));
    connect(joinRadio,SIGNAL(clicked()),this,SLOT(joinSelected()));

}

InitDialog::~InitDialog() {
}

void InitDialog::buttonClicked() {
    statusLabel->setText(tr("Connecting..."));
    emit validateDialog(InitVector(createRadio->isChecked(),portField->text(),hostField->text()));
}

void InitDialog::validated(QString message) {
    statusLabel->clear();
    if(message.isEmpty()) {
        hide();
        emit switchToSettings();
    }else {
        QMessageBox msgBox;
        msgBox.setText(tr("An error has occurred."));
        msgBox.setInformativeText(message);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
}

void InitDialog::createSelected() {
    hostField->setText(getIP());
    hostField->setEnabled(false);
}

void InitDialog::joinSelected() {
    //hostField->clear();
    hostField->setEnabled(true);
    hostField->setFocus();
}

void InitDialog::showDialog() {
    show();
}

QString InitDialog::getIP() {
    // We have not found a way to obtain the IP address of the default/primary network device
    return "127.0.0.1";
}
