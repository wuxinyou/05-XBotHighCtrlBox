!cross_compiler {
 BUILD_ARCH =  host
}
CONFIG += 1??????¡§??????¡ì????¡ì????????¡ì?o????¡ì????¡ì??? \
 ?????¡ì???????¡ì????????¡§??????¡ì????¡ì??????¡ì???????¨¬?????¨¬??????¡ì????? \
 debug_and_releas \
 qt3d \
 release \
 warn_on
CONFIG(debug, debug|release) {
 QMAKE_LIBS +=  -lcustomplugin  -lhmi3dplugin
}
CONFIG(release, debug|release) {
 QMAKE_LIBS +=  -lcustomplugin  -lhmi3dplugin
}
DEFINES = BLACK_BACKGROUND
DEPENDPATH += .
DESTDIR = bin/$$BUILD_ARCH
EM_HV = EM_HORIZONTAL
EM_TYPE = EM5000
INCLUDEPATH += .
MOC_DIR = build//$$BUILD_ARCH
OBJECTS_DIR = build/$$BUILD_ARCH
QT += sql
TARGET =
TEMPLATE = app
UI_DIR = build//$$BUILD_ARCH
cross_compiler {
 BUILD_ARCH =  target
}
HEADERS += src/abstractmeter.h \
 src/battery.h \
 src/compass.h \
 src/ctrsize.h \
 src/functions.h \
 src/glviewwidget.h \
 src/mainframe.h \
 src/model.h \
 src/modle_2d.h \
 src/mythreadport.h \
 src/pitch.h \
 src/roll.h \
 src/signalshow.h \
 src/speed.h \
 src/speedgrade.h \
 src/virtualDisjunctor.h \
 src/widgetwithbackground.h \
 src/light.h \
 src/videoFlag.h \
 src/change3d.h \
 src/videoDis.h
FORMS += ui/mainframe.ui ui/videoDis.ui
SOURCES += src/abstractmeter.cpp \
 src/battery.cpp \
 src/compass.cpp \
 src/ctrsize.cpp \
 src/functions.cpp \
 src/glviewwidget.cpp \
 src/main.cpp \
 src/mainframe.cpp \
 src/model.cpp \
 src/modle_2d.cpp \
 src/mythreadport.cpp \
 src/pitch.cpp \
 src/roll.cpp \
 src/signalshow.cpp \
 src/speed.cpp \
 src/speedgrade.cpp \
 src/virtualDisjunctor.cpp \
 src/widgetwithbackground.cpp \
 src/light.cpp \
 src/videoFlag.cpp \
 src/change3d.cpp \
 src/videoDis.cpp
RESOURCES += newfile.qrc
