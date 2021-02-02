/*  Autore: cavallo gabriele
 *  Fornisce delle funzioni per la gestione delle impostazioni
 *
 * */

#pragma once

#include <QString>
#include <QStringList>
#include "threads/settingswriter.h"
#include "file_types/settings.h"
#include "file_types/group.h"
#include "file_types/key.h"
#include "threads/settingsreader.h"

/// Scrive le impostazioni di default del programma in un percorso legacy
static void writeDefaultSettings(Settings *application_settings){
    // Formatto un oggetto impostazioni
    Settings *global_settings = new Settings();
    application_settings = global_settings;
    global_settings->setName("arduino-pacman-settings");
    global_settings->setDescription("Arduino pacman settings file for storing options. ");
    // Imposto il percorso del file
    global_settings->setFilePath(formatPathForOs(QDir::currentPath(), QStringList("settings/settings.stc")));
    qInfo() << "Avvio scrittura impostazioni sul disco. " << endl <<
             "file utilizzato: " << global_settings->getFilePath() << endl;
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
    g->addKey(new Key("libsearchpath-windows", "$CURPATH$/libsrc.src"));
    g->addKey(new Key("default-package-path", "$OSHOME$/ArduinoPacManPackages/"));
    g->addKey(new Key("base-package-name", "NewPackage"));

    global_settings->addGroup(g);

    // Gruppo con le informazioni sul sistema operativo e le impostazioni dei comandi
    Group *os_info = new Group();
    os_info->setName("os-selective");
    os_info->addKey(new Key("open-in-files-command-windows", "explorer %1"));
    os_info->addKey(new Key("open-in-files-command-linux", "nautilus %1"));
    os_info->addKey(new Key("open-in-files-command-macos", ".."));

    os_info->addKey(new Key("open-in-terminal-windows", "cmd /K %1"));
    os_info->addKey(new Key("open-in-terminal-linux", "??"));

    global_settings->addGroup(os_info);

    global_settings->setCreationDate(QDate::currentDate());

    // Avvio la scrittura delle impostazioni
    SettingsWriter *writer = new SettingsWriter();
    writer->setSettings(global_settings);
    writer->start();
}

static void readDefaultSettings(Settings *application_settings){
    application_settings = new Settings();
    application_settings->setFilePath(formatPathForOs(QDir::currentPath(), QStringList("settings/settings.stc")));

    SettingsReader *reader = new SettingsReader();
    reader->setSettingsObject(application_settings);
    reader->start();

    // Anntedo che finisca
    while(reader->isRunning()){}
}
