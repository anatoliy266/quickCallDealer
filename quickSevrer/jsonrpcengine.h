#ifndef JSONRPCENGINE_H
#define JSONRPCENGINE_H

#include <QObject>
#include <QHash>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariant>
#include <QDateTime>

#include <QDebug>

#include <jsonrpcparams.h>

#include <cstdlib>
#include <string>

using namespace JParam;

class JsonRpcEngine : public QObject
{
    Q_OBJECT
public:
    explicit JsonRpcEngine(QObject *parent = nullptr);
    QString _method(KerioMethod method = NoMethod);
    std::string generate(KerioMethod method, QHash<KerioParams, QVariant> params);
    QHash<QString, QVariant> parse(QString jString);
    QHash<KerioParams, QVariant> checkRequiredParams(KerioMethod method, QHash<KerioParams, QVariant> params);

signals:

public slots:
private:


};

#endif // JSONRPCENGINE_H
