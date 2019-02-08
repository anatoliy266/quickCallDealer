#ifndef DIFFMODEL_H
#define DIFFMODEL_H

#include <QObject>
#include <QStandardItemModel>
#include <QStandardItem>

class DiffModel : public QStandardItemModel
{
    Q_OBJECT
    static QStandardItemModel init(QString table, QList<QVariantList> data);
public:
    explicit DiffModel(QObject* parent = nullptr);
    void generateRoleNames(QString table);
    virtual QHash<int, QByteArray> roleNames() const;
    virtual QVariant data(const QModelIndex &idx, int role) const;
    Q_INVOKABLE void authorization(QString user, QString pwd);
    //Q_INVOKABLE void queueData(QString table, int filter = -1);
    Q_INVOKABLE void trayIconChangeEvent(int num);
    void setTableName(QString table);
    QString tableName();
signals:
    void authSucess();
    void userProperties(QString user, qlonglong number);
    void sucess();
    void cSucess();
    void hSucess();
    void nothing(QString table);
    void modelDataChange();

    void userInLine();
    void userNotInLine();
public slots:
    void model(QString table, QList<QVariantList> data);
private:
    QHash<int, QByteArray> role_names;
    int dataFilter = 0;
    QList<QVariantList> _data;
    QString _tableName;
};

#endif // DIFFMODEL_H
