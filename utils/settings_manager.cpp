/*  Autore: cavallo gabriele
 *  Fornisce delle funzioni per la gestione delle impostazioni
 *
 * */

#pragma once

#include <QString>
#include <QStringList>
#include "threads/settingswriterasync.h"
#include "settings/settings.h"
#include "settings/group.h"
#include "settings/key.h"
#include "threads/settingsreaderasync.h"

/// Scrive le impostazioni di default del programma in un percorso legacy
static void writeDefaultSettings(Settings *application_settings){
    // Formatto un oggetto impostazioni
    Settings *global_settings = new Settings();
    application_settings = global_settings;
    global_settings->setName("arduino-pacman-settings");
    global_settings->setDescription("Arduino pacman settings file for storing options. ");
    // Imposto il percorso del file
    global_settings->setFilePath(formatPathForOs(QDir::currentPath(), QStringList("settings/settings.stc")));
    // Groppo per le impostazioni di visualizzazione generale
    Group *group = new Group();
    group->setName("global-appearence");
    group->addKey(new Key("window-size", "500x500", AttributeList(new Attribute("um", "pixel"))));
    group->addKey(new Key("show-mode-default", "normal"));
    group->addKey(new Key("theme", "dark"));
    group->addKey(new Key("dark-theme-path", "$CURRENT$/themes/dark_theme.qcc"));
    group->addKey(new Key("light-theme-path", "$CURRENT$/themes/light_theme.qcc"));

    global_settings->addGroup(group);
    Group *gr = new Group();
    gr->setName("global-startup");
    gr->addKey(new Key("show-home-page", "true"));
    gr->addKey(new Key("open-recents", "false"));
    global_settings->addGroup(gr);

    // Gruppo per le impostazioni dei vari percorsi
    Group *g = new Group();
    g->setName("paths");
    g->addKey(new Key("libsearchpath", "$CURPATH$/libsrc.src"));
    g->addKey(new Key("default-package-path", "$OSHOME$/ArduinoPacManPackages/"));
    g->addKey(new Key("default-sources-path", "$OSHOME$/Sources/"));
    g->addKey(new Key("base-package-name", "NewPackage"));

    global_settings->addGroup(g);

    // Gruppo con le informazioni sul sistema operativo e le impostazioni dei comandi
    Group *os_info = new Group();
    os_info->setName("os-selective");
    os_info->addKey(new Key("open-in-files-windows", "explorer"));
    os_info->addKey(new Key("open-in-files-linux", "nautilus"));
    os_info->addKey(new Key("open-in-files-macos", ".."));

    os_info->addKey(new Key("open-in-terminal-windows", "cmd /K"));
    os_info->addKey(new Key("open-in-terminal-macos", ".."));
    os_info->addKey(new Key("open-in-terminal-linux", "gnome-terminal --working-directory="));

    global_settings->addGroup(os_info);

    global_settings->setCreationDate(QDate::currentDate());

    // Avvio la scrittura delle impostazioni
    auto *writer = new SettingsWriterAsync();
    writer->setSettings(global_settings);
    writer->start();
}

static void readDefaultSettings(Settings *application_settings){
    application_settings = new Settings();
    application_settings->setFilePath(formatPathForOs(QDir::currentPath(), QStringList("settings/settings.stc")));

    auto *reader = new SettingsReaderAsync();
    reader->setSettingsObject(application_settings);
    reader->start();

    // Anntedo che finisca
    while(reader->isRunning()){}
}
