TARGET =
DEPENDPATH += .
INCLUDEPATH += .
CONFIG += warn_on \
 release \
 qt3d \
 ??：???：?????━?：：??：???′?′??：???? \
 1????━?：：????：o?：：?? \
 debug_and_releas
cross_compiler {
 BUILD_ARCH =  target
}
!cross_compiler {
 BUILD_ARCH =  host
}
DEFINES = BLACK_BACKGROUND
EM_TYPE = EM5000
EM_HV = EM_HORIZONTAL
CONFIG(release, debug|release) {
 QMAKE_LIBS +=  -lcustomplugin  -lhmi3dplugin
}
CONFIG(debug, debug|release) {
 QMAKE_LIBS +=  -lcustomplugin  -lhmi3dplugin
}
DESTDIR = bin/$$BUILD_ARCH
OBJECTS_DIR = build/$$BUILD_ARCH
MOC_DIR = build//$$BUILD_ARCH
UI_DIR = build//$$BUILD_ARCH
FORMS += ui/mainframe.ui
HEADERS += src/mainframe.h \
 src/glviewwidget.h \
 src/model.h \
 src/abstractmeter.h \
 src/widgetwithbackground.h \
 src/functions.h \
 src/compass.h \
 src/speed.h \
 src/roll.h \
 src/pitch.h \
 src/battery.h \
 src/speedgrade.h \
 src/ctrsize.h \
 src/signalshow.h \
 src/focaldis.h \
 src/mythreadport.h \
 src/select.h \
 src/modle_2d.h \
 src/devwdm.h
SOURCES += src/mainframe.cpp \
 src/main.cpp \
 src/glviewwidget.cpp \
 src/model.cpp \
 src/abstractmeter.cpp \
 src/widgetwithbackground.cpp \
 src/functions.cpp \
 src/compass.cpp \
 src/speed.cpp \
 src/roll.cpp \
 src/pitch.cpp \
 src/battery.cpp \
 src/speedgrade.cpp \
 src/ctrsize.cpp \
 src/signalshow.cpp \
 src/focaldis.cpp \
 src/mythreadport.cpp \
 src/select.cpp \
 src/modle_2d.cpp
QT += sql
TEMPLATE = app
