#include "filejson.h"
#include <QDebug>

ToJson::ToJson(QObject *parent) : QObject(parent)
{

}

QString ToJson::reloadfile()
{
    QFile file(QStringLiteral("C:/Users/shotu/Desktop/QBBE-release/devices - 複製.json"));
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can't open file due to " << file.errorString();
    }
    else
    {
        QByteArray text = file.readAll();
        file.close();
        QJsonDocument m_doc(QJsonDocument::fromJson(text));
        QJsonObject m_obj;
        QJsonObject m_obj_1;
        QString result;
        if(m_doc.isObject()){
            m_obj = m_doc.object();
            if(!m_obj.find("device")->isNull()){
                m_obj_1 = m_obj.find("device")->toObject();
                qDebug() << m_obj_1;
                int obj_cnt = m_obj_1.size();
                result.append(m_obj_1["Load"].toString() + "<br>");
                for(int cnt = 0; cnt < (obj_cnt - 1); cnt++)
                {
                    QString tmp = "Item" + QString::number(cnt);
                    QJsonObject tmp_1 = m_obj_1[tmp].toObject();
                    result.append(QString::number(cnt) + ": " + tmp_1["model"].toString() + "<br>");
                    qDebug() << "tmp =" + tmp + " tmp_1 = " << tmp_1;
                }
                return result;
            }
        }
    }
    return nullptr;
}

void ToJson::writetodevice()
{
    QFile file(url);
    QJsonObject m_obj;
    QJsonDocument save;
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can't open file due to " + file.errorString();
    }
    else
    {
        QByteArray text = file.readAll();
        file.close();
        QJsonDocument m_doc(QJsonDocument::fromJson(text));
        if(m_doc.isObject())
        {
            m_obj = m_doc.object();
            QJsonObject m_obj_1 = m_obj["device"].toObject();
            m_obj["device"] = m_obj_1;
        }
    }
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Can't open file due to " + file.errorString();
    }
    else
    {
        QJsonDocument save(m_obj);
        file.write(save.toJson());
    }
}

bool ToJson::login(QString account, QString password)
{
    QFile file("C:/Users/shotu/Desktop/QtWebApp/Demo1/etc/docroot/users.json");
    if(!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "Can't open file due to " + file.errorString();
    }
    QByteArray text = file.readAll();
    QJsonDocument m_doc(QJsonDocument::fromJson(text));
    QJsonObject m_obj;
    QString m_obj_1;
    if(m_doc.isObject())
    {
        m_obj= m_doc.object();
        if(!m_obj.find(account)->isNull()){
            m_obj_1 = m_obj[account].toString();
        }
        if(password == m_obj_1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
