#ifndef DATASOCKET_H
#define DATASOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>

class DataSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit DataSocket(QObject *parent = nullptr);
    ~DataSocket();
signals:
    void responseData(QByteArray data);
    void establishedConnection();
    void failedConnection();
public slots:
    void writeRequest(QByteArray data);
    void readResponse();
    void prepareConnection();
    void sDebug(qint64 bytes);
    void lastWindowClosed();
    void stateChange(QAbstractSocket::SocketState state);
private:
    QByteArray _response;
};

#endif // DATASOCKET_H
