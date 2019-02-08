#include "datasocket.h"
#include <QDebug>

DataSocket::DataSocket(QObject* parent): QTcpSocket(parent)
{

}

DataSocket::~DataSocket()
{

}

void DataSocket::writeRequest(QByteArray data)
{
//    qDebug() << Q_FUNC_INFO << data.size();
//    qDebug() << Q_FUNC_INFO << this->state();
//    qDebug() << Q_FUNC_INFO << "write to socket";
    this->write(data);
    this->flush();
}

void DataSocket::readResponse()
{
    QByteArray _resp = this->readAll();
    QByteArray __resp = _resp.right(QByteArray("end").size());
    qDebug() << Q_FUNC_INFO << quint32(_resp.size());
    if (__resp == QByteArray("end"))
    {
        emit responseData(_response);
        _response.clear();
    } else {
        _response.append(_resp);
    }
}

void DataSocket::prepareConnection()
{
    qDebug() << "prepare connection called";
    this->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
    this->connectToHost("192.168.25.68", 50051, QIODevice::ReadWrite);
    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(readResponse()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(bytesWritten(qint64)), this, SLOT(sDebug(qint64)));
    QObject::connect(this, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(stateChange(QAbstractSocket::SocketState)));

    /*if(this->stateChanged())
    {
        qDebug() << "connected";
        emit establishedConnection();
    } else {
        qDebug() << "connection failed";
        emit failedConnection();
    }
    this->waitForBytesWritten();*/
}

void DataSocket::stateChange(QAbstractSocket::SocketState state)
{
    qDebug() << "State changed";
    if (state == QAbstractSocket::ConnectedState)
    {
        emit establishedConnection();
    }
    if (state == QAbstractSocket::ClosingState)
    {
        emit failedConnection();
    }
}

void DataSocket::sDebug(qint64 bytes)
{
    //qDebug() << bytes;
}

void DataSocket::lastWindowClosed()
{
    QByteArray request;
    QDataStream in(&request, QIODevice::ReadWrite);
    QString table = "destroy";
    QString query = "";
    in << quint8();
    in << table;
    in << query;
    in.device()->seek(0);
    in << quint8(request.size() - sizeof (quint8));
    this->write(request);
    this->flush();
    this->disconnectFromHost();
}
