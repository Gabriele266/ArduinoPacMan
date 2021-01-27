QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	file_types/libsearchpathlist.cpp \
    gui/generalstatusbar.cpp \
    gui/packagemanager.cpp \
    gui/packagetab.cpp \
	newsearchpath.cpp \
	packages/attributeditem.cpp \
	packages/dependency.cpp \
	packages/library.cpp \
    main.cpp \
    mainwindow.cpp \
    newpackagedialog.cpp \
	packages/natural.cpp \
	packages/package.cpp \
	packages/source.cpp \
    pacman_info.h \
	searchpathmanager.cpp \
	threads/librariesloader.cpp \
	threads/packagereader.cpp \
	threads/searchpathlistreader.cpp \
	threads/searchpathlistwriter.cpp \
	threads/sourceslister.cpp \
	threads/sourcesloader.cpp \
	utils/utils.cpp \
	packages/version.cpp

HEADERS += \
	file_types/libsearchpathlist.h \
    gui/generalstatusbar.h \
    gui/packagemanager.h \
    gui/packagetab.h \
	newsearchpath.h \
	packages/attributeditem.h \
	packages/dependency.h \
	packages/library.h \
    mainwindow.h \
    newpackagedialog.h \
	packages/natural.h \
	packages/package.h \
	packages/source.h \
	packages/version.h \
	searchpathmanager.h \
	threads/librariesloader.h \
	threads/packagereader.h \
	threads/searchpathlistreader.h \
	threads/searchpathlistwriter.h \
	threads/sourceslister.h \
	threads/sourcesloader.h \
	utils/costants.h \
	utils/macros.h

FORMS += \
    gui/generalstatusbar.ui \
    gui/packagemanager.ui \
    gui/packagetab.ui \
    mainwindow.ui \
    newpackagedialog.ui \
    newsearchpath.ui \
    searchpathmanager.ui

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

RESOURCES += \
	icons/icons.qrc
