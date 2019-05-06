#include "users_page.h"

users_page::users_page()
{

}

void users_page::service(HttpRequest &request, HttpResponse &response)
{
    if(request.getParameter("users") == "write")
    {
        QFile user_file("C:/Users/shotu/Desktop/QtWebApp/Demo1/etc/docroot/users.json");
        QJsonObject m_obj;
        if(user_file.open(QIODevice::ReadOnly))
        {
            QByteArray usertext = user_file.readAll();
            QJsonDocument m_doc(QJsonDocument::fromJson(usertext));
            m_obj = m_doc.object();
            user_file.close();
        }
        if(user_file.open(QIODevice::WriteOnly))
        {
            QString Jvalue = request.getParameter("password");
            m_obj.insert(request.getParameter("account"), Jvalue);
            QJsonDocument save_doc(m_obj);
            user_file.write(save_doc.toJson());
        }
        user_file.close();
    }
    response.setHeader("Content-Type", "text/html; charset=utf-8");
    response.setCookie(HttpCookie("firstCookie","hello",600,QByteArray(),QByteArray(),QByteArray(),false,true));
    response.setCookie(HttpCookie("secondCookie","world",600));

    QFile file("C:/Users/shotu/Desktop/QtWebApp/Demo1/etc/docroot/users.html");
    QFile user_file("C:/Users/shotu/Desktop/QtWebApp/Demo1/etc/docroot/users.json");
    QByteArray usertext;
    QString insert_item = nullptr;
    if(!user_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Can't open user file";
    }
    else
    {
        usertext = user_file.readAll();
        QJsonDocument m_doc(QJsonDocument::fromJson(usertext));
        QJsonObject m_obj = m_doc.object();
        QStringList keys = m_obj.keys();
        QStringList values = QStringList();
        QString key;
        foreach(key, keys)
        {
            values.append(m_obj[key].toString());
        }
        for(int cnt = 0; cnt < keys.length(); cnt++)
        {
            insert_item.append("<tr>");
            insert_item.append("<td>");
            insert_item.append(keys[cnt]);
            insert_item.append("</td>");
            insert_item.append("<td>");
            insert_item.append(values[cnt]);
            insert_item.append("</td>");
            insert_item.append("</tr>");
        }
        user_file.close();
    }
    if(file.open(QIODevice::ReadOnly))
    {
        QString body = file.readAll();
        int index = body.indexOf("All users's data");
        int index_1 = body.indexOf("</tr>", index);
        body.insert(index_1, insert_item);
        response.write(body.toUtf8(), true);
        file.close();
    }
    else
    {
        response.write("404 not found", true);
    }

}
