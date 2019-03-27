QT += core
QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp
TEMPLATE = app

QMAKE_LFLAGS += -F/System/Library/Frameworks/
LIBS += -L/usr/local/Cellar/glfw/3.2.1/lib -lglfw.3.2
LIBS += -L/usr/local/Cellar/glew/2.1.0/lib -lglew.2.1
LIBS += -framework OpenGL \
        -framework Cocoa \
        -framework CoreVideo \
        -framework IOKit \


INCLUDEPATH += /usr/local/include
DEPENDPATH += /usr/local/include

#DEFINES += GLEW_STATIC

copydata.commands = $(COPY_DIR) $$PWD/shader $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

DISTFILES += \
    shader/shader.frag \
    shader/shader.vert

