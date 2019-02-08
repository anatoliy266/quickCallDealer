#include "databaseengine.h"
#include <QDebug>

DataBaseEngine::DataBaseEngine(QObject* parent, QSqlDatabase db): QSqlRelationalTableModel(parent, db)
{
    connect(this, SIGNAL(upd()), this, SLOT(updateModel()));
}

DataBaseEngine::~DataBaseEngine()
{

}

bool DataBaseEngine::select()
{
    bool tQ = QSqlRelationalTableModel::select();
    if (tQ)
        generateRoleNames();
    return tQ;
}

void DataBaseEngine::generateRoleNames()
{
    role_names.clear();
    for (int i = 0; i<record().count(); i++)
    {
        role_names[Qt::UserRole + i + 1]=record().fieldName(i).toUtf8();
    }
}

QVariant DataBaseEngine::data(const QModelIndex &item, int role) const
{
    if (item.row() >= rowCount())
            return QString();

        if (role < Qt::UserRole)
            return QSqlQueryModel::data(item, role);
        else
        {
            int columnIdx = role - Qt::UserRole - 1;
            QModelIndex modelIndex = this->index(item.row(), columnIdx);
            return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
        }
}

void DataBaseEngine::updateModel()
{

    this->select();
    while(this->canFetchMore())
    {
        this->fetchMore();
    }
    this->generateRoleNames();
}

bool DataBaseEngine::setTablesList(QStringList tables)
{
    tablesList.clear();
    tablesList = tables;
    return true;
}

QByteArray DataBaseEngine::dBProceed(int id, QString tablename, QString filter)
{
    //qDebug() << id << tablename << filter;
    QByteArray result;
    this->setTable(tablename);
    if (filter != "")
    {
        this->setFilter(filter);
    }
    if (tablename == "callsDealer")
    {
        this->setRelation(2, QSqlRelation("orgsPhones", "orgPhone", "orgName"));
        this->setRelation(4, QSqlRelation("agentPhones", "agentPhone", "agentsName"));
        this->setRelation(5, QSqlRelation("time", "unixTime", "strTime"));
        this->setSort(0, Qt::DescendingOrder);
    }
    emit upd();
    //qDebug() << this->rowCount();

    QList<QVariantList> list;
    QVariant data;
    for (int i = 0; i< this->rowCount(); i++)
    {
        QVariantList _dList;
        for (int j = 0; j< this->columnCount(); j++)
        {
            data = this->data(this->index(i, j), Qt::DisplayRole);
            _dList.append(data);
        }
        list.append(_dList);
        _dList.clear();
    }
    qDebug() << "data count " << list.count();

    //prepare result
    QDataStream out(&result, QIODevice::ReadWrite);
    out << quint8(0);
    out << this->rowCount();
    out << this->columnCount();
    out << list;
    out.device()->seek(0);
    out << quint8(result.size()-sizeof(quint8));
    this->database().close();
    return result;
}

