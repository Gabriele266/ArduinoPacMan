/*  Autore: cavallo gabriele
 *  Rappresenta un thread per scrivere le impostazioni sul relativo file
 *
 * */

#ifndef SETTINGSWRITER_H
#define SETTINGSWRITER_H

#include <QThread>
#include "settings/settings.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>
#include <QDomDocument>
#include <QDomElement>

#include "utils/macros.h"

///    Rappresenta un thread per scrivere le impostazioni sul relativo file
class SettingsWriter : public QThread
{
public:
    SettingsWriter();

    void run();

    GETTER_SETTERC(Settings*, settings, Settings,
                   Imposta il puntatore alle impostazioni da scrivere su disco,
                   Restituisce un puntatore alle impostazioni da scrivere sul disco)
private:
    // Impostazioni da scrivere
    Settings *settings = nullptr;
};

#endif // SETTINGSWRITER_H
