#-------------------------------------------------
#
# Project created by QtCreator 2015-06-04T10:35:35
#
#-------------------------------------------------

QT       += core gui sql webkitwidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StartupWeekend
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    constants.cpp \
    application.cpp \
    newuser.cpp \
    existinguser.cpp \
    updateuser.cpp \
    smtp.cpp

HEADERS  += login.h \
    constants.h \
    application.h \
    newuser.h \
    existinguser.h \
    updateuser.h \
    smtp.h

FORMS    += login.ui \
    application.ui

QMAKE_CXXFLAGS += -Wno-enum-compare
DISTFILES +=
