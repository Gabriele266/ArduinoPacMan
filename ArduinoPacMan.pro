QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gui/packagemanager.cpp \
    gui/packagetab.cpp \
    library.cpp \
    main.cpp \
    mainwindow.cpp \
    newpackagedialog.cpp \
    package.cpp \
    pacman_info.h \
    utils.cpp \
    version.cpp

HEADERS += \
    gui/packagemanager.h \
    gui/packagetab.h \
    library.h \
    mainwindow.h \
    newpackagedialog.h \
    package.h \
    version.h

FORMS += \
    gui/packagemanager.ui \
    gui/packagetab.ui \
    mainwindow.ui \
    newpackagedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
	gui/info \
	icons/Apri.png \
	icons/Apri.xcf \
	icons/Chiudi.png \
	icons/Chiudi.xcf \
	icons/Documentation.png \
	icons/Documentation.xcf \
	icons/Export.png \
	icons/Import.png \
	icons/Import.xcf \
	icons/Information.png \
	icons/Information.xcf \
	icons/Nuovo.png \
	icons/Nuovo.xcf \
	icons/ProgramIcon.ico \
	icons/ProgramIcon.png \
	icons/ProgramIcon.xcf \
	icons/Properties.png \
	icons/Properties.xcf \
	icons/Structure.png \
	icons/Structure.xcf \
	icons/contract.xcf \
	icons/export.xcf \
	icons/library_viewer/Library.png \
	icons/library_viewer/Library.xcf \
	icons/library_viewer/Package.png \
	icons/library_viewer/Package.xcf \
