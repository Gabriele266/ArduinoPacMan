QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	settings/attribute.cpp \
	settings/group.cpp \
	settings/key.cpp \
	settings/libsearchpathlist.cpp \
	settings/settings.cpp \
    gui/generalstatusbar.cpp \
	gui/homepage.cpp \
	gui/libraryinfo.cpp \
    gui/packagetab.cpp \
	gui/tab.cpp \
	gui/newpackagedialog.cpp \
	gui/newsearchpath.cpp \
	gui/packageinfo.cpp \
	packages/attributeditem.cpp \
	packages/dependency.cpp \
	packages/library.cpp \
    main.cpp \
    mainwindow.cpp \
	packages/natural.cpp \
	packages/package.cpp \
	packages/source.cpp \
    pacman_info.h \
	gui/searchpathmanager.cpp \
	themes/theme.cpp \
	threads/fileloader.cpp \
	threads/librariesloader.cpp \
	threads/packagereader.cpp \
	threads/searchpathlistreader.cpp \
	threads/searchpathlistwriter.cpp \
	threads/settingsreader.cpp \
	threads/settingswriter.cpp \
	threads/sourcesloader.cpp \
	threads/srcdependencylister.cpp \
	utils/settings_manager.cpp \
	utils/startup.cpp \
	utils/utils.cpp \
	packages/version.cpp

HEADERS += \
	settings/attribute.h \
	settings/group.h \
	settings/key.h \
	settings/libsearchpathlist.h \
	settings/settings.h \
    gui/generalstatusbar.h \
	gui/libraryinfo.h \
	gui/homepage.h \
    gui/packagetab.h \
	gui/tab.h \
	gui/newpackagedialog.h \
	gui/newsearchpath.h \
	gui/packageinfo.h \
	packages/attributeditem.h \
	packages/dependency.h \
	packages/library.h \
    mainwindow.h \
	packages/natural.h \
	packages/package.h \
	packages/source.h \
	packages/version.h \
	gui/searchpathmanager.h \
	themes/theme.h \
	threads/fileloader.h \
	threads/librariesloader.h \
	threads/packagereader.h \
	threads/searchpathlistreader.h \
	threads/searchpathlistwriter.h \
	threads/settingsreader.h \
	threads/settingswriter.h \
	threads/sourcesloader.h \
	threads/srcdependencylister.h \
	utils/costants.h \
	utils/macros.h \
	utils/utils.h

FORMS += \
	gui/libraryinfo.ui \
    gui/generalstatusbar.ui \
    gui/homepage.ui \
    gui/packagetab.ui \
	gui/newpackagedialog.ui \
    mainwindow.ui \
	gui/newsearchpath.ui \
	gui/packageinfo.ui \
	gui/searchpathmanager.ui

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
	icons/dependencies.png \
	icons/export.xcf \
	icons/library_viewer/Library.png \
	icons/library_viewer/Library.xcf \
	icons/library_viewer/Package.png \
	icons/library_viewer/Package.xcf \

RESOURCES += \
	icons/icons.qrc
