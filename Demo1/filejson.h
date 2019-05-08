#ifndef TOJSON_H
#define TOJSON_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>

#include "httprequest.h"
#include "httpresponse.h"
#include "httprequesthandler.h"

class ToJson : public QObject
{
    Q_OBJECT
public:
    explicit ToJson(QObject *parent = nullptr);

    QString reloadfile();

    QString reloaddevices();

    bool login(QString, QString);

    void writetodevice();

    QString url = "C:/Users/shotu/Desktop/QBBE-release/devices - 複製.json";

signals:

public slots:
};

#endif // TOJSON_H
