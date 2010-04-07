/* 
 * File:   SettingsDialog.cpp
 * Author: pavel
 * 
 * Created on 31. březen 2010, 12:19
 */

#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QObject* parent = NULL, SettingsModel* _model) : QObject(parent) {

    model = _model;

    // TODO final GUI

    tempLabel = new QLabel("Player overview GUI here",this);
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel, Qt::Horizontal, this);
    startButton = new QPushButton(tr("Start game"),this);

    QGridLayout* layout = new QGridLayout();

    layout->addWidget(tempLabel,0,0,1,3,Qt::AlignLeft);
    layout->addWidget(buttonBox,1,0,1,2,Qt::AlignRight);
    layout->addWidget(startButton,1,2,1,1,Qt::AlignLeft);

    setLayout(layout);

    tempLabel->show();
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
    // TODO
}


void SettingsDialog::reload() {

    // TODO
    startButton->setEnabled(model->isCreating());
}

void SettingsDialog::cancelClicked() {
    emit disconnect();
}

void SettingsDialog::createClicked() {
    emit startGame();
}