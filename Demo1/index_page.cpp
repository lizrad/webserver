#include "index_page.h"
#include <QVariant>
#include <QDateTime>

index_page::index_page()
{

}

void index_page::service(HttpRequest &request, HttpResponse &response)
{
    Q_UNUSED(request);
    response.setHeader("Content-Type", "text/html; charset=utf-8");
    response.setCookie(HttpCookie("firstCookie","hello",600,QByteArray(),QByteArray(),QByteArray(),false,true));
    response.setCookie(HttpCookie("secondCookie","world",600));

    QFile file("C:/Users/shotu/Desktop/QtWebApp/Demo1/etc/docroot/index.html");
    QByteArray body;
    if(file.open(QIODevice::ReadOnly))
    {
        body = file.readAll();
    }
    response.write(body,true);
    file.close();
}
