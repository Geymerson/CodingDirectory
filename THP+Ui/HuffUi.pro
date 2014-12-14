#-------------------------------------------------
#
# Project created by QtCreator 2014-12-14T07:54:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HuffUi
TEMPLATE = app


SOURCES += main.cpp\
        mainWindow.cpp\
        Decoding.cpp\
        Encoding.cpp\
        HuffmanInfo.cpp


HEADERS  += mainWindow.h\
         Decoding.h\
         Encoding.h\
         Node.h\
         LinkedList.h\
         ListADT.h\
         HuffmanInfo.h

FORMS    += mainWindow.ui
