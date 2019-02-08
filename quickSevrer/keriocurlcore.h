#ifndef KERIOCURLCORE_H
#define KERIOCURLCORE_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QIODevice>

#include <curl/curl.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include <jsonrpcparams.h>
#include <jsonrpcengine.h>

class KerioCurlCore : public QObject
{
    Q_OBJECT
public:
    explicit KerioCurlCore(QObject *parent = nullptr);
    static size_t writer(char* contents, size_t nmemb, size_t size, std::string *data);
    std::string prepare(KerioMethod method, QHash<KerioParams, QVariant> params, JsonRpcEngine *jrpc);
    std::string setUrl(std::string host, int port, std::string target);
    QHash<QString, QVariant> perform(KerioMethod method, QHash<KerioParams, QVariant> params, std::string host = "ats.550550.ru", int port = 4021, std::string target = "/admin/api/jsonrpc/");
    bool read_cookies(CURL* curl);

signals:

public slots:
};

#endif // KERIOCURLCORE_H
