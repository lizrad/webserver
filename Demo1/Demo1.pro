# This project demonstrates how to use QtWebAppLib by including the
# sources into this project.

TARGET = Demo1
TEMPLATE = app
QT = core network
CONFIG += console

HEADERS += \
           ../../../Documents/FileReadWrite/filejson.h \
           devices_page.h \
           index_page.h \
           login.h \
           setting_page.h \
           src/requestmapper.h \
           src/controller/dumpcontroller.h \
           src/controller/templatecontroller.h \
           src/controller/formcontroller.h \
           src/controller/fileuploadcontroller.h \
           src/controller/sessioncontroller.h \
           users_page.h

SOURCES += src/main.cpp \
           ../../../Documents/FileReadWrite/filejson.cpp \
           devices_page.cpp \
           index_page.cpp \
           login.cpp \
           setting_page.cpp \
           src/requestmapper.cpp \
           src/controller/dumpcontroller.cpp \
           src/controller/templatecontroller.cpp \
           src/controller/formcontroller.cpp \
           src/controller/fileuploadcontroller.cpp \
           src/controller/sessioncontroller.cpp \
           users_page.cpp

OTHER_FILES += etc/* etc/docroot/* etc/templates/* etc/ssl/* logs/* ../readme.txt

#---------------------------------------------------------------------------------------
# The following lines include the sources of the QtWebAppLib library
#---------------------------------------------------------------------------------------

include(../QtWebApp/logging/logging.pri)
include(../QtWebApp/httpserver/httpserver.pri)
include(../QtWebApp/templateengine/templateengine.pri)
# Not used: include(../QtWebApp/qtservice/qtservice.pri)
