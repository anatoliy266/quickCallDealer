#include "diffmodel.h"
#include <QDebug>

DiffModel::DiffModel(QObject *parent): QStandardItemModel (parent)
{
    this->setRowCount(1);
    this->setColumnCount(1);
    QStandardItem* item = new QStandardItem();
    item->setData(QVariant("nothing"), Qt::DisplayRole);
    this->setItem(0,0,item);
}

QVariant DiffModel::data(const QModelIndex &idx, int role) const
{
    if (role >= Qt::UserRole+1)
    {
        int row = idx.row();
        int col = role-Qt::UserRole-1;
        return QVariant(this->item(row, col)->data(Qt::DisplayRole));
    } else {
        return QVariant("");
    }
}

QHash<int, QByteArray> DiffModel::roleNames() const
{
    return role_names;
}

void DiffModel::generateRoleNames(QString table)
{
    role_names.clear();
    if (table == "users")
    {
        role_names[Qt::UserRole+1] = "id_user";
        role_names[Qt::UserRole+2] = "user";
        role_names[Qt::UserRole+3] = "password";
        role_names[Qt::UserRole+4] = "number";
        role_names[Qt::UserRole+5] = "inLine";
    }

    if (table == "orgsPhones")
    {
        role_names[Qt::UserRole+1] = "orgPhone";
        role_names[Qt::UserRole+2] = "orgName";
        role_names[Qt::UserRole+3] = "userName";
        role_names[Qt::UserRole+4] = "image";
    }

    if (table == "query_type")
    {
        role_names[Qt::UserRole+1] = "q_id";
        role_names[Qt::UserRole+2] = "q_type";
    }

    if (table == "callsDealer")
    {
        role_names[Qt::UserRole+1] = "id_call";
        role_names[Qt::UserRole+2] = "callerPhone";
        role_names[Qt::UserRole+3] = "callerName";
        role_names[Qt::UserRole+4] = "agentPhone";
        role_names[Qt::UserRole+5] = "agentName";
        role_names[Qt::UserRole+6] = "dateTime";
        role_names[Qt::UserRole+7] = "asterCallId";
        role_names[Qt::UserRole+8] = "asterChannelState";
        role_names[Qt::UserRole+9] = "asterOrgUser";
        role_names[Qt::UserRole+10] = "comment";
        role_names[Qt::UserRole+11] = "query";
        role_names[Qt::UserRole+12] = "rec";
        role_names[Qt::UserRole+13] = "writed";
    }
    for (int i = 0; i < roleNames().count(); i++)
    {
        QStandardItem* item = new QStandardItem();
        item->setData(QVariant(""), Qt::DisplayRole);
        this->setItem(0,i, item);
        //emit dataChanged(index(0,i), index(0,i));
    }
}

void DiffModel::model(QString table, QList<QVariantList> data)
{
    if (roleNames().count() == 0)
        this->generateRoleNames(table);

    int prev_rows = 0;
    if (rowCount() == 0)
    {
        prev_rows = 0;
    } else {
        prev_rows = rowCount();
    }
    qDebug() << Q_FUNC_INFO << data.count() << prev_rows;
    if (data.count() == 0)
    {
        emit nothing(tableName());
    } else {
        if (rowCount() < data.count())
        {
            qDebug() << "data count MORE THEN rowCount()";
            this->insertRows(rowCount()-1, data.count()-rowCount());
        }
        if (rowCount() > data.count())
        {
            qDebug() << "data count LESS THEN rowCount()";
            this->removeRows(data.count()-1, rowCount()-data.count());
        }
        emit modelDataChange();
        for (int i = 0; i < data.count(); i++)
        {
            //qDebug() << prev_rows << i << data.count() << rowCount() << columnCount() << roleNames().count();
            for (int j = 0; j < roleNames().count(); j++)
            {
               // qDebug() << j;
                QStandardItem*_item = new QStandardItem();
                _item->setData(data.value(i).value(j), Qt::DisplayRole);
                this->setItem(i,j, _item);
                //qDebug() << this->item(i,j)->data(Qt::DisplayRole);
            }
            emit dataChanged(index(i,0), index(i, roleNames().count()-1) ,{Qt::DisplayRole});
        }
        //signals to dtControl when model data is ready
        if (roleNames().count() > 10)
        {
            if (this->item(0,roleNames().count()-1)->data(Qt::DisplayRole) == QVariant(0))
                emit cSucess();
            else
                emit hSucess();
        } else {
            emit sucess();
        }
    }
}

void DiffModel::authorization(QString user, QString pwd)
{
    int _pwd = pwd.toInt();
    for (int i = 0; i < this->rowCount(); i++)
    {
        if (this->item(i,1)->data(Qt::DisplayRole).toString() == user && this->item(i,2)->data(Qt::DisplayRole).toInt() == _pwd)
        {
            qDebug() << Q_FUNC_INFO << "auth sucess";
            emit authSucess();
            emit userProperties(user, this->item(i,3)->data(Qt::DisplayRole).toLongLong());
            break;
        } else {
            qDebug() << Q_FUNC_INFO << "auth failed";
        }
    }
}



void DiffModel::trayIconChangeEvent(int num)
{
    for (int i = 0; i < rowCount(); i++)
        if (this->item(i, 3)->data(Qt::DisplayRole) == QVariant(num))
        {
            if (this->item(i, 4)->data(Qt::DisplayRole) == QVariant(1))
            {
                emit userInLine();
            } else {
                emit userNotInLine();
            }
        }
}

void DiffModel::setTableName(QString table)
{
    _tableName = table;
}

QString DiffModel::tableName()
{
    return _tableName;
}
