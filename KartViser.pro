# -------------------------------------------------
# Project created by QtCreator 2009-11-05T15:03:24
# -------------------------------------------------
QT += opengl
TARGET = KartViser
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    gshhspolygons.cpp \
    gshhsp.cpp \
    kartwidget.cpp
HEADERS += mainwindow.h \
    proj_api.h \
    gshhspolygons.h \
    gshhsp.h \
    kartwidget.h
FORMS += mainwindow.ui
INCLUDEPATH += $$quote(C:/3party/proj-4.7.0/src)
DEPENDPATH += $$quote(C:/3party/proj-4.7.0/src)
LIBS += -LC:/3party/proj-4.7.0/src \
    -lproj
OTHER_FILES += ../../../../3party/gshhs/README.TXT
