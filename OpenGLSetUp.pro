QT += core
QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += GLEW_STATIC

#If want to use test framework please turn on this define
#DEFINES += USE_TEST_FRAMEWORK

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    vertexbuffer.cpp \
    indexbuffer.cpp \
    vertexarray.cpp \
    shader.cpp \
    opengl_debug.cpp \
    renderer.cpp \
    texture.cpp \
    stb_image.cpp \
    imgui/example_reference.cpp \
    imgui/imgui_demo.cpp \
    imgui/imgui_draw.cpp \
    imgui/imgui_impl_glfw.cpp \
    imgui/imgui_impl_opengl3.cpp \
    imgui/imgui_widgets.cpp \
    imgui/imgui.cpp \
    test_framework/test.cpp \
    test_framework/test_clearcolor.cpp \
    test_framework/test_texture2d.cpp

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

copydata.commands = $(COPY_DIR) $$PWD/res $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

DISTFILES += \
    res/shader/shader.frag \
    res/shader/shader.vert \
    res/texture/image.png

HEADERS += \
    vertexbuffer.h \
    indexbuffer.h \
    vertexarray.h \
    vertexbufferlayout.h \
    shader.h \
    opengl_debug.h \
    renderer.h \
    stb_image.h \
    texture.h \
    imgui/imconfig.h \
    imgui/imgui_impl_glfw.h \
    imgui/imgui_impl_opengl3.h \
    imgui/imgui_internal.h \
    imgui/imgui.h \
    imgui/imstb_rectpack.h \
    imgui/imstb_textedit.h \
    imgui/imstb_truetype.h \
    test_framework/test.h \
    test_framework/test_clearcolor.h \
    test_framework/test_texture2d.h


#fix warning when cast to void*
#QMAKE_CXXFLAGS += -Wno-int-to-void-pointer-cast
