#ifndef LISTENSERVER_H
#define LISTENSERVER_H

#include <QObject>
#include <QTcpServer>

class ListenServer: public QTcpServer
{
    Q_OBJECT
public:
    explicit ListenServer(QObject* parent = nullptr);
    virtual void incomingConnection(qintptr socketDesc) override;
signals:
    void newIncomingConnection(qintptr socketDesc);
};

#endif // LISTENSERVER_H
