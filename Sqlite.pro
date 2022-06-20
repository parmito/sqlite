QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets qml quick

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CustomQSqlTableModel.cpp \
    dbmanager.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CustomQSqlTableModel.h \
    dbmanager.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Sqlite_pt_BR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/assets/img/fruits.png \
    android/assets/db/dbSqlite.db \
    android/build.gradle \
    android/gradle.properties \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

    deployment.files += dbSqlite.db
    deployment.path = /assets/db
    INSTALLS += deployment

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

RESOURCES += \
    qt.qrc
