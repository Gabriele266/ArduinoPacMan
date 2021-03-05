/*
 * Rappresenta un elemento con un nome
 * */

#ifndef NAMEDITEM_H
#define NAMEDITEM_H

#include <QString>

#include "utils/macros.h"

class NamedItem
{
public:
    NamedItem();
    NamedItem(QString name);

    /**
      @brief Imposta il nome dell' oggetto
      */
    GETTER(QString, name, Name)

    /**
      @brief Restituisce il nome dell' oggetto
      */
    SETTER(QString, name, Name)


    /**
     * @brief operator == Confronta due oggetti con nome
     * @param item Oggetto con cui confrontarlo
     * @return true se hanno lo stesso nome
     */
    bool operator==(NamedItem &item);

    /**
     * @brief hasSameName Determina se questo oggetto e un altro hanno lo stesso nome
     * @param item
     * @return true se sono uguali.
     */
    bool hasSameName(NamedItem &item);

private:
    QString name;
};

#endif // NAMEDITEM_H
