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

#ifndef _SETTINGSMODEL_H
#define	_SETTINGSMODEL_H


#include <QObject>
#include <QtCore>

class SettingsModel : public QObject {

    Q_OBJECT

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

    virtual qint32 getMaxRoundTime();
    virtual void setMaxRoundTime(qint32 _maxRoundTime);

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

    qint32 maxRoundTime;

    QVector<Player> players;
    
     */
};

#endif	/* _SETTINGSMODEL_H */

