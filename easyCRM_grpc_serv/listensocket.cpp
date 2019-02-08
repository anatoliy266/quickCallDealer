#include "listensocket.h"
#include <QtNetwork>


ListenSocket::ListenSocket(QObject *parent): QObject(parent)
{

}

ListenSocket::~ListenSocket()
{

}

/*void ListenSocket::runListenServer()
{
    ListenServer* listenServer = new ListenServer();

    QObject::connect(listenServer, SIGNAL(newInconingConnection(qintptr)), this, SLOT(newIncomingConnection(qintptr)), Qt::QueuedConnection);
    if (listenServer->listen(QHostAddress::Any, 50051))
    {
        qDebug() << "Server started";
    } else {
        qDebug() << "Sever not started";
        listenServer->close();
    }
    listenServer->waitForNewConnection();
}

void ListenSocket::newIncomingConnection(qintptr socketDescriptor)
{
    QThread* thread = new QThread();
    NewConnectionWorker* newConWork = new NewConnectionWorker();
    workersList.append(std::make_shared<NewConnectionWorker>(newConWork));
    QObject::connect(this, SIGNAL(setSocketHandler(qintptr)), newConWork, SLOT(setSocketHandler(qintptr)), Qt::QueuedConnection);
    QObject::connect(thread, SIGNAL(finished()), newConWork, SLOT(deleteLater()));
    QObject::connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    newConWork->moveToThread(thread);
    thread->start();
    emit setSocketHandler(socketDescriptor);
}*/

void ListenSocket::runKerioWorker()
{
    GeneralWorker* kerioWork = new GeneralWorker();
    QTimer* tmr = new QTimer();
    tmr->setInterval(1500);
    QThread* _thread = new QThread();
    qDebug() <<"Listen Socket: kerio : thread " << _thread;
    QObject::connect(tmr, SIGNAL(timeout()), kerioWork, SLOT(read()), Qt::BlockingQueuedConnection);
    QObject::connect(kerioWork, SIGNAL(dataChanged(QString)), this, SLOT(dataChanged(QString)));
    kerioWork->moveToThread(_thread);
    _thread->start();
    tmr->start();
}

void ListenSocket::dataChanged(QString table)
{
    qDebug() << table;
}
