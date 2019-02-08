#ifndef DATABUFFER_H
#define DATABUFFER_H

#include <QObject>
#include <QByteArray>
#include <QList>
#include <QVariant>
#include <QVariantList>
#include <QDataStream>
#include <QIODevice>
#include <QHash>

class DataBuffer : public QObject
{
    Q_OBJECT
public:
    explicit DataBuffer(QObject *parent = nullptr);
signals:
    void orgsData(QString table, QList<QVariantList> data);
    void usersData(QString table, QList<QVariantList> data);
    void querysData(QString table, QList<QVariantList> data);
    void callsData(QString table, QList<QVariantList> data);
    void usersPrepared();
    void orgsPrepared();
    void querysPrepared();
    void callsPrepared();
public slots:
    void recieveFromServer(QByteArray data);
    void askForTableData(QString table, int filter = -1);
private:
    QHash<QString, QList<QVariantList>> buffer;
};

#endif // DATABUFFER_H
