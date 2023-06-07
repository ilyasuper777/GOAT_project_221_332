QT += testlib
QT -= gui
QT += network

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_unit_test_for_the_exam.cpp \
    ../../server/mytcpserver-ex.cpp

SUBDIRS += \
    ../../server/echoServer.pro

HEADERS += \
    ../../server/mytcpserver-ex.h
