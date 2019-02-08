#include "listenserver.h"

ListenServer::ListenServer(QObject* parent): QTcpServer(parent)
{

}

void ListenServer::incomingConnection(qintptr socketDesc)
{
    emit newIncomingConnection(socketDesc);
}
