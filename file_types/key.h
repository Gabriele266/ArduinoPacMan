/*
 * Autore: cavallo gabriele
 * Rappresenta una chiave nelle impostazioni
 * costituita da un nome e un valore e degli attributi addizionali
 */

#ifndef KEY_H
#define KEY_H

#include <QString>
#include <QFile>
#include "utils/macros.h"
#include <QDomElement>
#include <QDomDocument>
#include <QStringList>
#include <QList>
#include <QMap>

#include "packages/natural.h"
#include "utils/utils.cpp"
#include "attribute.h"

/// Rappresenta una chiave
class Key
{
public:
    Key();
    Key(QString name, QString value);
    Key(QString name, QString value, AttributeList attributes);


    GETTER_SETTERC(QString, name, Name,
                   Imposta il nome della chiave,
                   Restituisce il nome della chiave)

    GETTER_SETTERC(QString, value, Value,
                   Imposta il valore della chiave,
                   Restituisce il valore della chiavve)

    /// Aggiunge l'alltributo name con il valore value alla chiave
    void addAttribute(QString name, QString value);

    /// Aggiunge l'attributo partendo da una tupla di stringhe
    void addAttribute(Attribute *attr);

    /// Imposta il valore dell' attributo con quel nome
    void setAttributeValue(QString attribute_name, QString value);

    /// Restituisce il valore dell' attributo con quel nome, altrimenti ""
    QString getAttributeValue(QString name);

    /// Restituisce l'attributo con quel nome
    Attribute* getAttributeByName(QString name);

    /// Restituisce l'attributo con quell' indice, altrimenti un attributo nullo
    Attribute* getAttributeByIndex(Natural index);

    /// Restituisce il numero di attributi della chiave
    Natural getAttributesCount();

private:
    // Nome della chiave
    QString name;
    // Valore della chiave
    QString value;
    // Lista di eventuali attributi
    AttributeList attributes;
};

#endif // KEY_H
