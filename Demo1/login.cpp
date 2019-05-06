#include "login.h"
#include <QDebug>

login::login()
{

}

void login::service(HttpRequest &request, HttpResponse &response)
{
    Q_UNUSED(request);
    response.setHeader("Content-Type", "text/html; charset=utf-8");
    response.setCookie(HttpCookie("firstCookie","hello",600,QByteArray(),QByteArray(),QByteArray(),false,true));
    response.setCookie(HttpCookie("secondCookie","world",600));

    QFile file("C:/Users/shotu/Desktop/QtWebApp/Demo1/etc/docroot/login.html");
    if(file.open(QIODevice::ReadOnly))
    {
        QString body = file.readAll();
        int index = body.indexOf("</form>");
        body.insert(index, "<br><p>帳號密碼不符合，請重新輸入</p>");
        response.write(body.toUtf8(), true);
        file.close();
    }
}
