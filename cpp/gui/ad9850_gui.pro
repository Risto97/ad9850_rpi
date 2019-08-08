CONFIG += qt
HEADERS += $$files(*.h, true)
HEADERS += $$files(*.hpp, true)
SOURCES += $$files(*.cpp, true)
SOURCES += $$files(../ad9850/*.cpp, true)

TARGET = program

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += /usr/local/include
INCLUDEPATH += ../ad9850
LIBS += -L/usr/local/lib -lwiringPi
