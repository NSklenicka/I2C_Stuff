QT -= gui
LIBS += -l bcm2835
CONFIG += c++11 console
CONFIG -= app_bundle

SOURCES += \
        main.cpp \
        nvm_24lc024.cpp

DISTFILES += \
    ../deleteMe.txt

HEADERS += \
    nvm_24lc024.h
