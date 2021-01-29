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

    /// Aggiunge una chiave alla lista
    void addKey(Key *k);

    /// Restituisce la chiave con quell' indice
    Key* getKey(Natural index);

    /// Restituisce la chiave con quel nome
    Key* getKey(QString name);

    /// Restituisce l'elemento xml per contenere questo gruppo
    QDomElement toElement();

    /// Prova a caricare un gruppo di chiavi dall' elemento el
    bool getFromElement(QDomElement el);

    /// Restituisce il numero di chiavi in questo gruppo
    Natural getKeysCount();
private:
    // Nome del gruppo
    QString name;
    // Lista delle chiavi
    QList<Key*> keys;
};

#endif // GROUP_H
