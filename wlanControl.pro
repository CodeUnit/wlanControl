QT       += widgets network svg
HEADERS   = src/MainWindow.h src/SettingsDialog.h
SOURCES   = src/MainWindow.cpp src/SettingsDialog.cpp src/main.cpp
RESOURCES = src/resource.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += images/*
