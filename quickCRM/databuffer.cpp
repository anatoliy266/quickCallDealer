#include "databuffer.h"
#include <QDebug>

DataBuffer::DataBuffer(QObject *parent) : QObject(parent)
{

}

void DataBuffer::recieveFromServer(QByteArray data)
{
    QByteArray _data = data;
    int _size = 0;
    QString table = "";
    int rowCount = 0;
    QList<QVariantList> list;
    QDataStream out(&_data, QIODevice::ReadOnly);
    out >> _size;
    qDebug() << _size;
    out >> table;
    qDebug() << table;
    out >> rowCount;
    qDebug() << rowCount;
    out >> list;
    qDebug() << list.count();

    qDebug() << Q_FUNC_INFO << table << rowCount << list.count();
    QStringList tList({"users", "orgsPhones", "query_type", "callsDealer"});
    buffer[table] = list;
    qDebug() << buffer[table].count();
    switch (tList.indexOf(table)) {
    case 0: {
        qDebug() << "users data prepared";
        emit usersPrepared();
        break;
    }
    case 1: {
        qDebug() << "orgs data prepared";
        emit orgsPrepared();
        break;
    }
    case 2: {
        emit querysPrepared();
        qDebug() << "query data prepared";
        break;
    }
    case 3: {
        emit callsPrepared();
        qDebug() << "calls data prepared";
        break;
    }
    default:
        break;
    }
}

void DataBuffer::askForTableData(QString table, int filter)
{
    qDebug() << Q_FUNC_INFO << table << filter;
    QStringList tList({"users", "orgsPhones", "query_type", "callsDealer"});
    switch (tList.indexOf(table)) {
    case 0: {
        QList<QVariantList> _data = buffer[table];
        qDebug() << Q_FUNC_INFO << _data.count() << "users";
        emit usersData(table, _data);
        break;
    }
    case 1: {
        QList<QVariantList> _data = buffer[table];
        qDebug() << Q_FUNC_INFO << _data.count() << "orgsPhones";
        emit orgsData(table, _data);
        break;
    }
    case 2: {
        QList<QVariantList> _data = buffer[table];
        qDebug() << Q_FUNC_INFO << _data.count() << "query_type";
        emit querysData(table, _data);
        break;
    }
    case 3: {
        QList<QVariantList> _data;
        for (int i = 0; i < buffer[table].count(); i++)
        {
            if (buffer[table].value(i).value(12).toInt() == filter)
            {
                _data.append(buffer[table].value(i));
            }
        }
        qDebug() << Q_FUNC_INFO << _data.count() << "callsDealer";
        emit callsData(table, _data);
        break;
    }
    default:
        break;
    }
}
