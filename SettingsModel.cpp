/* 
 * File:   SettingsModel.cpp
 * Author: pavel
 * 
 * Created on 31. březen 2010, 18:19
 */

#include "SettingsModel.h"

SettingsModel::SettingsModel() {
}

SettingsModel::~SettingsModel() {
}


bool SettingsModel::isCreating() {
    return create;
}

void SettingsModel::setCreating(bool _create) {
    create = _create;
}


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


quint32 SettingsModel::getMaxRoundTime() {
    return maxRoundTime;
}

void SettingsModel::setMaxRoundTime(quint32 _maxRoundTime) {
    maxRoundTime = _maxRoundTime;
}


void SettingsModel::addPlayer(Player player) {

    // TODO

}

void SettingsModel::updatePlayer(Player player) {

    // TODO

}

void SettingsModel::removePlayer(quint8 playerID) {

    // TODO

}

quint8 SettingsModel::getPlayerCount() {
    return players.size();
}

Player SettingsModel::getPlayerAt(quint8 index) {

    // TODO assert?

    return players[index];
}

