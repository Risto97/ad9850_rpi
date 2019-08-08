CONFIG += qt
HEADERS += $$files(*.h, true)
HEADERS += $$files(*.hpp, true)
SOURCES = $$files(*.cpp, true)
TARGET = program

QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
