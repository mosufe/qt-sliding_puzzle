QT += widgets

SOURCES = main.cpp \
    button.cpp \
    pixmap.cpp \
    view.cpp

RESOURCES = slidingpuzzle.qrc
# install
target.path = /home/guilherme/Projects/qt-projects/slidingpuzzle
INSTALLS += target

HEADERS += \
    resources.h
