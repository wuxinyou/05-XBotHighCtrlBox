

CONFIG += qt warn_on release
HEADERS += src/abstractmeter.h \
 src/battery.h \
 src/compass.h \
 src/ctrsize.h \
 src/functions.h \
 src/mainframe.h \
 src/modle_2d.h \
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
 src/videoDis.h \
 src/coord.h \
 src/camera.h \
 src/processImage.h \
 src/serialPortThread.h \
 src/YUV2RGBThread.h \
 src/dataType.h \
 src/cyQueue.h
FORMS += ui/mainframe.ui ui/videoDis.ui
SOURCES += src/abstractmeter.cpp \
 src/battery.cpp \
 src/compass.cpp \
 src/ctrsize.cpp \
 src/functions.cpp \
 src/main.cpp \
 src/mainframe.cpp \
 src/modle_2d.cpp \
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
 src/videoDis.cpp \
 src/coord.cpp \
 src/camera.cpp \
 src/processImage.cpp \
 src/serialPortThread.cpp \
 src/YUV2RGBThread.cpp \
 src/cyQueue.cpp
RESOURCES += newfile.qrc
