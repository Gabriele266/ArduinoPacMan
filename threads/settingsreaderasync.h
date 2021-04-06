/*  Autore: cavallo gabriele
 *  Rappresenta un thread per la lettura di un file di impostazioni sul disco
 * */

#ifndef SETTINGSREADERASYNC_H
#define SETTINGSREADERASYNC_H

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
#include "utils/utils.h"

#include "exceptions/filenotfoundexception.h"
#include "exceptions/nullpointerexception.h"

/// Rappresenta un thread per la lettura delle impostazioni dal disco
class SettingsReaderAsync : public QThread
{
public:
    SettingsReaderAsync();

    GETTER_SETTERC(Settings*, settings, SettingsObject,
                   Imposta le impostazioni a cui aggiungere le informazioni lette e da cui trovare il file,
                   Restituisce le impostazioni lette)

    void run();
private:
    // Impostazioni da cui leggere le informazioni
    Settings* settings = nullptr;
};

#endif // SETTINGSREADERASYNC_H
