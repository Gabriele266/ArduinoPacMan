/* Autore: cavallo gabriele
 * Rappresenta un gruppo di chiavi di impostazione
 *
 * */

#ifndef GROUP_H
#define GROUP_H

#include <QList>
#include "key.h"
#include <QString>

/// Rappresenta un gruppo di chiavi di impostazione
class Group
{
public:
    Group();

    GETTER_SETTERC(QString, name, Name,
                   Imposta il nome del gruppo,
                   Restituisce il nome del gruppo)

    GETTER_SETTERC(QString, description, Description,
                   Imposta la descrizione del gruppo,
                   Restituisce la descrizione del gruppo)
    /// Aggiunge una chiave alla lista
    void addKey(Key *k);

    /// Restituisce la chiave con quell' indice
    Key* getKey(Natural index);

    /// Restituisce la chiave con quel nome
    Key* getKey(QString name);

    /// Prova a caricare un gruppo di chiavi dall' elemento el
    bool getFromElement(QDomElement el);

    /// Restituisce il valore della chiave con quel nome, altrimenti una stringa nulla
    QString getValue(QString key_name);

    /// Restituisce il numero di chiavi in questo gruppo
    Natural getKeysCount();
private:
    // Nome del gruppo
    QString name;
    // Descrizione del gruppo
    QString description;
    // Lista delle chiavi
    QList<Key*> keys;
};

#endif // GROUP_H
