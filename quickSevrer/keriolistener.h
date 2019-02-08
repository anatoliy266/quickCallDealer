#ifndef KERIOLISTENER_H
#define KERIOLISTENER_H

#include <QObject>
#include <QSqlDatabase>

class KerioListener : public QObject
{
    Q_OBJECT
public:
    explicit KerioListener(QObject *parent = nullptr);
    QSqlDatabase *prepareDBConnection();


signals:

public slots:
};

#endif // KERIOLISTENER_H
