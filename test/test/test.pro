QT += testlib
QT -= gui
QT += network #Для работы с сетью

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_test.cpp \
    ../../server/mytcpserver.cpp

SUBDIRS += \
    ../../server/echoServer_351.pro

HEADERS += \
    ../../server/mytcpserver.h
