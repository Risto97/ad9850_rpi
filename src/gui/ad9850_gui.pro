CONFIG += qt
CONFIG += c++17
HEADERS += $$files(*.h, true)
HEADERS += $$files(*.hpp, true)
SOURCES += $$files(*.cpp, true)
SOURCES += $$files(../ad9850/*.cpp, true)
SOURCES += $$files(../common/*.cpp, true)

TARGET = program

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += /usr/local/include
INCLUDEPATH += ../ad9850
INCLUDEPATH += ../common/

LIBS += -L/usr/local/lib -lconfig++ -lstdc++fs -lwiringPi
