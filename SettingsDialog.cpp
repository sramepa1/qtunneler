/* 
 * File:   SettingsDialog.cpp
 * Author: pavel
 * 
 * Created on 31. březen 2010, 12:19
 */

#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(SettingsModel* _model) {

    model = _model;

    // TODO final GUI

    statusLabel = new QLabel(tr("Initializing..."),this);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel, Qt::Horizontal, this);
    startButton = new QPushButton(tr("Start game"),this);

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(statusLabel,0,0,1,3,Qt::AlignLeft);
    layout->addWidget(buttonBox,1,0,1,2,Qt::AlignRight);
    layout->addWidget(startButton,1,2,1,1,Qt::AlignLeft);

    setLayout(layout);

    statusLabel->show();
    buttonBox->show();
    startButton->show();

    connect(buttonBox,SIGNAL(rejected()),this,SLOT(cancelClicked()));
    connect(startButton,SIGNAL(clicked()),this,SLOT(createClicked()));
}

SettingsDialog::~SettingsDialog() {
}

void SettingsDialog::showSettings() {
    reload();
    show();
}


void SettingsDialog::hideSettingsAndSwitch() {
    hide();
}


void SettingsDialog::reload() {
    startButton->setEnabled(model->isCreating() && model->isReady());
    statusLabel->setText(model->getStatus());
}

void SettingsDialog::cancelClicked() {
    emit disconnect();
}

void SettingsDialog::createClicked() {
    emit startGame();
}