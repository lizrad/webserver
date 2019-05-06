#include "devices_page.h"

devices_page::devices_page()
{

}

void devices_page::service(HttpRequest &request, HttpResponse &response)
{
    if(request.getParameter("devices") == "write")  //若有觸發按鈕
    {
        QFile device_file("C:/Users/shotu/Desktop/QBBE-release/devices - 複製.json");
        QJsonObject m_obj;
        if(device_file.open(QIODevice::ReadOnly))   //先用Read讀進檔案，再使用write修改檔案，才不會蓋掉原先的檔案。
        {
            QByteArray usertext = device_file.readAll();
            QJsonDocument m_doc(QJsonDocument::fromJson(usertext));
            m_obj = m_doc.object();
            device_file.close();
        }
        if(device_file.open(QIODevice::WriteOnly))
        {
            QString Jvalue = request.getParameter("Load");
            QJsonObject m_obj_1 = m_obj["device"].toObject();
            m_obj_1.insert("Load", Jvalue);
            m_obj["device"] = m_obj_1;
            QJsonDocument save_doc(m_obj);
            device_file.write(save_doc.toJson());
            device_file.close();
        }
    }
    //下面是更新顯示的網頁
    QFile device_file("C:/Users/shotu/Desktop/QBBE-release/devices - 複製.json");
    if(device_file.open(QIODevice::ReadOnly))
    {
        QString text = device_file.readAll();
        QJsonDocument m_doc(QJsonDocument::fromJson(text.toUtf8()));
        keys = readkeys(m_doc);
        values = readvalues(m_doc);
    }
    //把要顯示的資料加到原本寫好的網頁上
    QFile file("C:/Users/shotu/Desktop/QtWebApp/Demo1/etc/docroot/devices_page.html");
    if(file.open(QIODevice::ReadOnly))
    {
        QString body = file.readAll();
        QString insert_item = nullptr;
        int index = body.indexOf("</tr>");
        for(int cnt = 0; cnt < keys.length(); cnt++)
        {
            insert_item.append("<tr>");
            insert_item.append("<td>");
            if(cnt == keys.length() -1)
            {
                insert_item.append("Load:");
                insert_item.append("</td>");
                insert_item.append("<td>");
                insert_item.append("<input name=\"Load\" value=\"");    //沒辦法直接讀取Table的Value，所以用Input
                insert_item.append(values[cnt]);
                insert_item.append("\"");
                insert_item.append("</td>");
                insert_item.append("</tr>");
            }
            else
            {
                insert_item.append("Item:" + QString::number(cnt));
                insert_item.append("</td>");
                insert_item.append("<td>");
                insert_item.append(values[cnt]);
                insert_item.append("</td>");
                insert_item.append("</tr>");
            }
        }
        body.insert(index, insert_item);
        response.write(body.toUtf8(), true);
        file.close();
    }
}

QStringList devices_page::readkeys(QJsonDocument m_doc)
{
    QStringList tmp = QStringList();
    QJsonObject m_obj_1 = m_doc.object();
    QJsonObject m_obj = m_obj_1["device"].toObject();
    tmp = m_obj.keys();

    return tmp;
}

QStringList devices_page::readvalues(QJsonDocument m_doc)
{
    QStringList tmp = QStringList();
    QJsonObject m_obj_1 = m_doc.object();
    QJsonObject m_obj = m_obj_1["device"].toObject();
    QString key;

    //讓讀到的Item按照順序排列。
    for(int cnt = 0; cnt < keys.length(); cnt++)
    {
        if(cnt == keys.length() -1)
        {
            if(m_obj[keys[cnt]].toString() != nullptr)
            {
                tmp.append(m_obj[keys[cnt]].toString());
            }
            else
            {
                tmp.append("No selected device");
            }
        }
        else
        {
            key = "Item" + QString::number(cnt);
            QJsonObject m_obj_2 = m_obj[key].toObject();
            tmp.append(m_obj_2["model"].toString());
        }
    }

    return tmp;
}
