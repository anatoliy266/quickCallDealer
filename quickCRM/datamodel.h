#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QByteArray>
#include <QDataStream>
#include <QIODevice>
#include <QHash>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QDebug>

#include <QAbstractItemModel>

#include "dataparams.h"

class DataModel: public QStandardItemModel
{
    Q_OBJECT
public:
    explicit DataModel(QObject* parent = nullptr);

signals:

public slots:
    void prepare(QByteArray data);
    void viewFilter(QString filter);
private:


};

#endif // DATAMODEL_H
