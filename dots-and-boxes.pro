TEMPLATE = app

QT += qml quick widgets

SOURCES += src/main.cpp \
    src/tile.cpp \
    src/boxesmodel.cpp

HEADERS += \
    src/tile.h \
    src/boxesmodel.h

OTHER_FILES += \
    qml/*.qml \
    android/AndroidManifest.xml

RESOURCES += resources.qrc

include(deployment.pri)

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
