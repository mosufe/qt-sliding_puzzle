QT += widgets core gui

SOURCES = main.cpp \
    button.cpp \
    pixmap.cpp \
    view.cpp \
    state.cpp \
    game.cpp \
    digitaltimer.cpp \
    input.cpp \
    recordwindow.cpp

RESOURCES = slidingpuzzle.qrc
# install
TARGET = app

HEADERS += \
    resources.h
