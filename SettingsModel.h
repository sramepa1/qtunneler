/* 
 * File:   SettingsModel.h
 * Author: pavel
 *
 * Created on 31. březen 2010, 18:19
 */

#ifndef _SETTINGSMODEL_H
#define	_SETTINGSMODEL_H


#include <QObject>
#include <QtCore>

#include "Player.h"

class SettingsModel : public QObject {

    Q_OBJECT

    // TODO declare Qt properties?

public:
    SettingsModel(QObject* parent = NULL);
    virtual ~SettingsModel();

    virtual bool isCreating() const;
    virtual void setCreating(bool _create);

    virtual bool isReady() const;
    virtual void setReady(bool _ready);

    virtual QString getStatus() const;
    virtual void setStatus(const QString _status);

    virtual quint16 getPort() const;
    virtual void setPort(quint16 _port);

    /*
     * QTunneler 2.0

    virtual quint8 getGameMode();
    virtual void setGameMode(quint8 _gameMode);

    virtual quint8 getNumRounds();
    virtual void setNumRounds(quint8 _numRounds);

    virtual quint32 getMaxRoundTime();
    virtual void setMaxRoundTime(quint32 _maxRoundTime);

    virtual void addPlayer(Player player);
    virtual void updatePlayer(Player player);
    virtual void removePlayer(quint8 playerID);

    virtual quint8 getPlayerCount();
    virtual Player getPlayerAt(quint8 index);
    
     
     */

public slots:


signals:
    

protected:

    bool create;
    bool ready;

    quint16 port;

    QString status;

    /*  QTunneler 2.0
     *
    quint8 gameMode;
    quint8 numRounds;

    quint32 maxRoundTime;

    QVector<Player> players;
    
     */
};

#endif	/* _SETTINGSMODEL_H */

