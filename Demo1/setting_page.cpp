#include "setting_page.h"

setting_page::setting_page()
{

}

void setting_page::service(HttpRequest &request, HttpResponse &response)
{
    QJsonDocument m_doc;
    QFile json_file("C:/Users/shotu/Desktop/QtWebApp/Demo1/etc/docroot/settings.json");
    if(request.getParameter("settings") == "write")
    {
        if(json_file.open(QIODevice::ReadOnly))
        {
            QString json_text = json_file.readAll();
            m_doc = QJsonDocument::fromJson(json_text.toUtf8());
            m_keys = findChildren(m_doc);
            json_file.close();
        }
        if(json_file.open(QIODevice::WriteOnly))
        {
            m_doc = updatekeys(request, m_doc);
            json_file.write(m_doc.toJson());
        }

    }
    if(json_file.open(QIODevice::ReadOnly))
    {
        QString json_text = json_file.readAll();
        m_doc = QJsonDocument::fromJson(json_text.toUtf8());
        m_keys = findChildren(m_doc);
        json_file.close();
    }
    QFile html_file("C:/Users/shotu/Desktop/QtWebApp/Demo1/etc/docroot/settings.html");
    if(html_file.open(QIODevice::ReadOnly))
    {
        QString insert_item = nullptr;
        QString body = html_file.readAll();
        int index = body.indexOf("Parameters:");
        int index_1 = body.indexOf("</tr>", index);
        foreach(QString m_key, m_keys)
        {
            insert_item.append("<tr>");
            insert_item.append("<td>");
            insert_item.append(m_key);
            insert_item.append("</td>");
            insert_item.append("<td>");
            insert_item.append("<input name=\"");
            insert_item.append(m_key);
            insert_item.append("\" value=\"");
            insert_item.append(findkeywords(m_doc, m_key));
            insert_item.append("\">");
            insert_item.append("</td>");
            insert_item.append("</tr>");
        }
        body.insert(index_1, insert_item);
        response.write(body.toUtf8(), true);
        html_file.close();
    }
    else
    {
        qWarning() << "File open error" + html_file.errorString();
    }
}

QString setting_page::findkeywords(QJsonDocument m_doc, QString key)
{
    QJsonObject m_obj = m_doc.object();
    QString tmp = m_obj[key].toString();

    return tmp;
}

QStringList setting_page::findChildren(QJsonDocument m_doc)
{
    QStringList tmp = QStringList();
    QJsonObject m_obj = m_doc.object();
    tmp = m_obj.keys();

    return tmp;
}

QJsonDocument setting_page::updatekeys(HttpRequest &request, QJsonDocument m_doc)
{
    QJsonObject m_obj = m_doc.object();
    foreach(QString key, m_keys)
    {
        QByteArray tmp_key = key.toUtf8();
        QByteArray text = request.getParameter("key1");
        m_obj.insert("key1", QString(text));
    }
    m_doc = QJsonDocument(m_obj);

    return m_doc;
}
