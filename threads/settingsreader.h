/*  Autore: cavallo gabriele
 *  Rappresenta un thread per la lettura di un file di impostazioni sul disco
 * */

#ifndef SETTINGSREADER_H
#define SETTINGSREADER_H

#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDomAttr>
#include <QDir>
#include <QThread>

#include "settings/settings.h"
#include "settings/attribute.h"
#include "settings/group.h"
#include "settings/key.h"

#include "packages/natural.h"

#include "utils/macros.h"
#include "utils/utils.cpp"

/// Rappresenta un thread per la lettura delle impostazioni dal disco
class SettingsReader : public QThread
{
public:
    SettingsReader();

    GETTER_SETTERC(Settings*, settings, SettingsObject,
                   Imposta le impostazioni a cui aggiungere le informazioni lette e da cui trovare il file,
                   Restituisce le impostazioni lette)

    void run();
private:
    // Impostazioni da cui leggere le informazioni
    Settings* settings = nullptr;
};

#endif // SETTINGSREADER_H
