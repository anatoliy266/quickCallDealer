#ifndef NEWCONNECTIONWORKER_H
#define NEWCONNECTIONWORKER_H

#include <QObject>
#include <QTcpSocket>

#include "databaseengine.h"

#include "params.h"

#include <QObject>
#include <QDataStream>
#include <QByteArray>
#include <QTcpServer>
#include <cstdlib>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlField>
#include <QSqlRecord>
#include <QSqlRelationalTableModel>
#include <QList>
#include <QVariant>
#include <QEventLoop>
#include <QEvent>
#include <QIODevice>
#include <QAbstractSocket>
#include <QString>
#include <QSqlError>
#include <error.h>
#include <cstdlib>
#include <iostream>
#include <exception>

enum DataMethod {
    getHistory,
    getCalls,
    getQuery,
    getUsers,
    getOrgs
};

typedef struct DataStruct {
    QString _table;
    int _rows;
    QString _query;
} dStruct;


class NewConnectionWorker: public QObject
{
    Q_OBJECT
public:
    explicit NewConnectionWorker(QObject* parent = nullptr);
    QSqlDatabase *prepareDBConnection();
    QString table();
    QString query();
    void processing(QString table, QString query);
signals:
public slots:
    void listenRead();
    void writeResp(QByteArray _result, int rows);
    void setSocketHandler(qintptr socketDescriptor);
private:
    //dStruct data;
};

#endif // NEWCONNECTIONWORKER_H
