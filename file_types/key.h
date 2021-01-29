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
#include <QMap>

#include "packages/natural.h"
#include "utils/utils.cpp"

/// Numero massimo di attributi per ogni chiave
#define MAX_KEY_ATTRIBUTES 5

/// Rappresenta una chiave
class Key
{
public:
    Key();

    Key(QString name, QString value);

    GETTER_SETTERC(QString, name, Name,
                   Imposta il nome della chiave,
                   Restituisce il nome della chiave)

    GETTER_SETTERC(QString, value, Value,
                   Imposta il valore della chiave,
                   Restituisce il valore della chiavve)

    /// Formatta una chiave a partire da una riga di testo
    static Key keyFromElement(QDomElement line);

    /// Carica la chiave da una stringa
    bool loadFromString(QDomElement str);

    /// Formatta la chiave e i suoi attributi in una stringa per far si che vengano salvati
    QDomElement getElement();

    /// Aggiunge l'alltributo name con il valore value alla chiave
    void addAttribute(QString name, QString value);

    /// Aggiunge l'attributo partendo da una tupla di stringhe
    void addAttribute(QMap<QString, QString> map);

    /// Restituisce il valore dell' attributo con quel nome, altrimenti ""
    QString getAttribute(QString name);

    /// Restituisce il numero di attributi della chiave
    Natural getAttributesCount();
private:
    // Nome della chiave
    QString name;
    // Valore della chiave
    QString value;
    // Lista di eventuali attributi
    QMap<QString, QString> additional_attributes;
};

#endif // KEY_H
