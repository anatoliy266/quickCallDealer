#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include <QObject>
#include <QList>
#include <QVariant>
#include <QVariantList>
#include <QThread>
#include <QByteArray>
#include <QTimer>
#include <QTime>
#include <QDate>
#include <QDateTime>
#include <QStandardItemModel>
#include <QImage>
#include <QFile>
#include <QSystemTrayIcon>
#include <QIcon>

#include "dataparams.h"
#include "diffmodel.h"

class DataController: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString user READ user WRITE setUser NOTIFY userChanged)
    Q_PROPERTY(qlonglong num READ num WRITE setNum NOTIFY numChanged)
public:
    explicit DataController(QObject* parent = nullptr);
    Q_INVOKABLE void init();
    Q_INVOKABLE void orgsRequest();
    Q_INVOKABLE void querysRequest();
    Q_INVOKABLE void usersRequest();
    Q_INVOKABLE void modelRequest(int userphone);
    Q_INVOKABLE void preloadSucess();
    Q_INVOKABLE void queueData(QString table, int filter);
//    Q_INVOKABLE void play();
    Q_INVOKABLE void setRecRequest(QString idx, QString userName, QString orgName, QString orgPhone, QString query, QString comment, QString image);
    void setUser(QString user);
    void setNum(qlonglong num);
    QString user();
    qlonglong num();
signals:
    void sendOToServer(QByteArray data);
    void sendQToServer(QByteArray data);
    void sendUpdToServer(QByteArray data);
    void sendToServer(QByteArray data);
    void modelData(QByteArray data);
    void setFilter(QString filter);
    void userChanged(QString user);
    void numChanged(qlonglong num);
    void callsFilter(int f);
    void historyFilter(int f);
    void establishedConnectionSignal();
    void failedConnectionSignal();
    void prepareConnection();
    void preloadSucessSignal();
    void usersSucessSignal();
    void callsSucessSignal();
    void orgsSucessSignal();
    void querysSucessSignal();
    void uModSucessSignal();
    void qModSucessSignal();
    void hModSucessSignal();
    void cModSucessSignal();
    void oModSucessSignal();
    void uModNYSignal();
    void qModNYSignal();
    void hModNYSignal();
    void cModNYSignal();
    void oModNYSignal();
    void authSucessSignal();
    void toBuffer(QString table, int filter);
public slots:
    void failedConnection();
    void establishedConnection();
    void userProperties(QString user, qlonglong number);
    void usersSucess();
    void callsSucess();
    void querysSucess();
    void orgsSucess();
    void authSucess();
    void nothing(QString table);
    void uModSucess();
    void cModSucess();
    void hModSucess();
    void oModSucess();
    void qModSucess();
private:
    QString _user;
    qlonglong _number;
};

#endif // DATACONTROLLER_H
