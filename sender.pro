QT -= gui
QT += dbus

SOURCES += sender.cpp

target.path = $$PWD/build
INSTALLS += target

HEADERS += \
    callbackclass.h
