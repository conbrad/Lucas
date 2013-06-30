#-------------------------------------------------
#
# Project created by QtCreator 2013-06-25T15:05:19
#
#-------------------------------------------------

QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EmailApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    IMAPParser.cpp \
    IMAPConnection.cpp \
    IMAPClient.cpp \
    Folder.cpp \
    Email.cpp

HEADERS  += mainwindow.h \
    IMAPTag.h \
    IMAPParser.h \
    IMAPConnection.h \
    IMAPClient.h \
    Folder.h \
    Email.h

FORMS    += mainwindow.ui
