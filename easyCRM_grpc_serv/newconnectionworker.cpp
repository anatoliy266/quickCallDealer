#include "newconnectionworker.h"

NewConnectionWorker::NewConnectionWorker(QObject *parent):QObject(parent)
{
    QTcpSocket* newConWorkSocket = new QTcpSocket(this);
    QObject::connect(newConWorkSocket, SIGNAL(readyRead()), this, SLOT(listenRead()));
    newConWorkSocket->waitForReadyRead();
}

QSqlDatabase* NewConnectionWorker::prepareDBConnection()
{
    auto* db1 = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    db1->setDatabaseName("P://1//123.db");
    db1->open();
    qDebug() << db1->lastError().text();
    db1->close();
    return db1;
}

void NewConnectionWorker::listenRead()
{
    dStruct data;
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(this->children().at(0));
    QByteArray requestStr = socket->readAll();
    socket = nullptr;
    quint8 size;
    QDataStream out(requestStr);
    out >> size;
    out >> data._table;
    out >> data._query;
    out >> data._rows;
    qDebug() << data._table << data._query;
    processing(data._table, data._query);
    socket->waitForReadyRead();
}

QString NewConnectionWorker::table()
{

}

QString NewConnectionWorker::query()
{

}

void NewConnectionWorker::writeResp(QByteArray _result, int rows)
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(this->children().at(0));

    qDebug() << _result.size();
    socket->waitForBytesWritten();
    while(true)
    {
        QByteArray _part = _result.left(1400);
        if (_result.size() < 1400)
        {
            qDebug() << _result.size() << "end part size";
            _result.remove(0, 1400);
            socket->write(_part);
            socket->flush();
            break;
        }
        qDebug() << _result.size() << "proceed size";
        _result.remove(0, 1400);
        socket->write(_part);
        socket->flush();
        this->thread()->msleep(1);
    }

    /*if (data._rows != rows)
    {

    } else {
        if (rows != 0)
        {
            socket->write(QByteArray("error!"));
            socket->flush();
        } else {
            socket->write(QByteArray("error!"));
            socket->flush();
        }
    }*/
    socket = nullptr;
}

void NewConnectionWorker::processing(QString table, QString query)
{
    QByteArray _result;
    int rows = 0;

    auto db1 = QSqlDatabase::addDatabase("QSQLITE");
    db1.setDatabaseName("P://1//123.db");
    QSqlError err;
    try {
        DataBaseEngine* dbEngine = new DataBaseEngine(this, db1);
        if (db1.open())
        {
            if (table == "setRecord")
            {
                qDebug() << query;
                QStringList _queryList = query.split("[delimiter]");
                for (int i = 0; i < _queryList.count(); i++)
                {
                    QSqlQuery query;
                    QString _q = _queryList.value(i);
                    qDebug() << _q;
                    query.prepare(_q);
                    if (query.exec())
                    {
                        _result = QByteArray("sucess");
                        query.clear();
                    } else {
                        _result = QByteArray("failed");
                        query.clear();
                    }
                    rows = 0;
                    qDebug() << _result << "insertion result";
                }
            } else {
                _result = dbEngine->dBProceed(0, table, query);
                rows  = dbEngine->rowCount();
            }
        } else {
            qDebug() << "not opened";
            err = db1.lastError();
        }
        dbEngine->clear();
        db1.close();
        db1.databaseName().clear();
        delete dbEngine;
        QString connection = db1.connectionName();
        db1.removeDatabase(connection);
        QSqlDatabase::removeDatabase(connection);
    } catch (QSqlError err) {

    }
    writeResp(_result, rows);
}

void NewConnectionWorker::setSocketHandler(qintptr socketHandler)
{
    //QTcpSocket* socket = qobject_cast<QTcpSocket*>(this->children().at(0));
    qobject_cast<QTcpSocket*>(this->children().at(0))->setSocketDescriptor(socketHandler);
}
