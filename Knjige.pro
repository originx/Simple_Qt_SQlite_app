#-------------------------------------------------
#
# Project created by QtCreator 2011-10-16T15:38:06
#
#-------------------------------------------------

QT       += core gui\
           sql
TARGET = Knjige
TEMPLATE = app


SOURCES += main.cpp\
        glavniprozor.cpp

HEADERS  += glavniprozor.h \
    connection.h \
    baza.h

FORMS    += glavniprozor.ui

OTHER_FILES += \
    baza.db
