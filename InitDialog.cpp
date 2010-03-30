/*
 * File:   InitDialog.cpp
 * Author: pavel
 *
 * Created on 19. březen 2010, 12:26
 */

#include "InitDialog.h"

InitDialog::InitDialog() {

    setWindowTitle("QTunneler");

    createRadio = new QRadioButton("Create game");
    joinRadio = new QRadioButton("Join game");
    hostLabel = new QLabel("host:");
    portLabel = new QLabel("port:");
    hostField = new QLineEdit();
    portField = new QLineEdit();
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

    hostLabel->setBuddy(hostField);
    portLabel->setBuddy(portField);

    createRadio->setParent(this);
    joinRadio->setParent(this);
    hostLabel->setParent(this);
    portLabel->setParent(this);
    hostField->setParent(this);
    portField->setParent(this);
    buttonBox->setParent(this);

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(createRadio,0,0,1,2,Qt::AlignLeft);
    layout->addWidget(joinRadio,1,0,1,2,Qt::AlignLeft);
    layout->addWidget(hostLabel,2,0,Qt::AlignRight);
    layout->addWidget(hostField,2,1);
    layout->addWidget(portLabel,3,0,Qt::AlignRight);
    layout->addWidget(portField,3,1);
    layout->addWidget(buttonBox,4,0,1,2,Qt::AlignRight);


    setLayout(layout);

    createRadio->setChecked(true);

    portField->setMaxLength(5);
    portField->setMinimumWidth(40);
    portField->setMaximumWidth(60);
    portField->setText("4242");

    hostField->setMaxLength(512);
    hostField->setMinimumWidth(256);
    hostField->setEnabled(false);
    hostField->setText("127.0.0.1"); // TODO find out actual IP

    createRadio->show();
    joinRadio->show();
    hostLabel->show();
    hostField->show();
    portLabel->show();
    portField->show();
    buttonBox->show();

    connect(buttonBox,SIGNAL(accepted()),this,SLOT(buttonClicked()));

    connect(createRadio,SIGNAL(clicked()),this,SLOT(createSelected()));
    connect(joinRadio,SIGNAL(clicked()),this,SLOT(joinSelected()));

}

InitDialog::~InitDialog() {
}

void InitDialog::buttonClicked() {
    emit validateDialog(InitVector(createRadio->isChecked(),portField->text(),hostField->text()));
}

void InitDialog::validated(QString message) {
    if(message.isEmpty()) {
        hide();
        emit switchToWindow();
    }else {
        QMessageBox msgBox;
        msgBox.setText("An error has occurred.");
        msgBox.setInformativeText(message);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.exec();
    }
}

void InitDialog::createSelected() {
    hostField->setText("127.0.0.1"); // TODO find out actual IP
    hostField->setEnabled(false);
}

void InitDialog::joinSelected() {
    hostField->clear();
    hostField->setEnabled(true);
}

void InitDialog::showDialog() {
    show();
}
