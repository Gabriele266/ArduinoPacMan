/*  Autore: cavallo gabriele
 *  Rappresenta un tab in un controllo multitab
 * */

#ifndef TAB_H
#define TAB_H

#include <QString>

#include "utils/macros.h"

/// Rappresenta un tab e fornisce delle funzioni per identificarlo
class Tab
{
public:
    Tab();

    GETTER_SETTERC(QString, name, Name,
                   Imposta il nome del tab,
                   Restituisce il nome del tab);

    GETTER_SETTERC(QString, attribute, Info,
                   Imposta gli attributi del tab,
                   Restituisce gli attributi del file);
private:
    // Nome del tab
    QString name;

    // Attributi del tab
    QString attribute;
};

#endif // TAB_H
