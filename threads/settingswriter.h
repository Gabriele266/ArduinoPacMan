/*  Autore: cavallo gabriele
 *  Rappresenta un thread per scrivere le impostazioni sul relativo file
 *
 * */

#ifndef SETTINGSWRITER_H
#define SETTINGSWRITER_H

#include <QThread>
#include "file_types/settings.h"
#include <QFile>
#include <QDir>
#include <QDomDocument>
#include <QDomElement>

#include "utils/macros.h"

///    Rappresenta un thread per scrivere le impostazioni sul relativo file
class SettingsWriter : public QThread
{
public:
    SettingsWriter();

    void run();

private:
    // Impostazioni da scrivere
    Settings *settings = nullptr;
};

#endif // SETTINGSWRITER_H
