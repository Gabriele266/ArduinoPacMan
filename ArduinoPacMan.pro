QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    library.cpp \
    main.cpp \
    mainwindow.cpp \
    newpackagedialog.cpp \
    package.cpp \
    packagemanager.cpp \
    packagetab.cpp \
    pacman_info.h \
    utils.cpp \
    version.cpp

HEADERS += \
    library.h \
    mainwindow.h \
    newpackagedialog.h \
    package.h \
    packagemanager.h \
    packagetab.h \
    version.h

FORMS += \
    mainwindow.ui \
    newpackagedialog.ui \
    packagetab.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
