/*
 *      -----------------------------------------------
 *      QTunneler - a classic DOS game remake in QT
 *      -----------------------------------------------
 *
 *      semestral project for API programming course
 *      (Y36API) at the FEE CTU Prague
 *
 *      Created by:
 *           Pavel Sramek (sramepa1@fel.cvut.cz)
 *           Martin Smarda (smardmar@fel.cvut.cz)
 *
 *      March & April 2010
 *
 *      This is free software, licensed under GNU LGPL
 *      (GNU Lesser General Public License, version 3)
 *      http://www.gnu.org/licenses/lgpl.html
 *
 *      Project homepage:
 *      http://code.google.com/p/qtunneler/
 *
 *      Version 1.0
 *
 */

#include "SettingsModel.h"

SettingsModel::SettingsModel(QObject* parent) : QObject(parent) {
    ready = false;
    create = false;
    port = 4242; //will be overwritten anyway...
}

SettingsModel::~SettingsModel() {
}


bool SettingsModel::isCreating() const {
    return create;
}

void SettingsModel::setCreating(bool _create) {
    create = _create;
}

bool SettingsModel::isReady() const {
    return ready;
}

void SettingsModel::setReady(bool _ready) {
    ready = _ready;
}

QString SettingsModel::getStatus() const {
    return status;
}

void SettingsModel::setStatus(const QString _status) {
    status = _status;
}

quint16 SettingsModel::getPort() const {
    return port;
}

void SettingsModel::setPort(quint16 _port) {
    port = _port;
}

/*  QTunneler 2.0
 *
quint8 SettingsModel::getGameMode() {
    return gameMode;
}

void SettingsModel::setGameMode(quint8 _gameMode) {
    gameMode = _gameMode;
}


quint8 SettingsModel::getNumRounds() {
    return numRounds;
}

void SettingsModel::setNumRounds(quint8 _numRounds) {
    numRounds = _numRounds;
}


qint32 SettingsModel::getMaxRoundTime() {
    return maxRoundTime;
}

void SettingsModel::setMaxRoundTime(qint32 _maxRoundTime) {
    maxRoundTime = _maxRoundTime;
}


void SettingsModel::addPlayer(Player player) {

    // not implemented

}

void SettingsModel::updatePlayer(Player player) {

    // not implemented

}

void SettingsModel::removePlayer(quint8 playerID) {

    // not implemented

}

quint8 SettingsModel::getPlayerCount() {
    return players.size();
}

Player SettingsModel::getPlayerAt(quint8 index) {

    // assert?

    return players[index];
}
*/
