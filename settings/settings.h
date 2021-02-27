/*  Autore: cavallo gabriele
 *  Rappresenta un file di configurazione
 * */

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <QStringList>
#include <QFile>
#include <QDomElement>
#include <QDomDocument>
#include <QDomNode>
#include <QDir>

#include "packages/attributeditem.h"
#include "utils/macros.h"
#include "utils/utils.cpp"

#include "key.h"
#include "group.h"

/// Rappresenta un file di impostazioni
class Settings : public AttributedItem
{
public:
    Settings();
    Settings(QString f);

    GETTER_SETTERC(QString, file_path, FilePath,
                   Imposta il file su cui scrivere le impostazioni,
                   Restituisce il file su cui scrivere le impostazioni)

    /// Aggiunge il gruppo alle impostazioni
    void addGroup(Group *g);

    /// Restituisce il gruppo con quell' indice
    Group* getGroup(Natural index);

    /// Restituisce un gruppo a partire dal nome
    Group* getGroup(QString byName);

    /// Aggiunge la chiave al gruppo con quel nome
    void addKey(QString grupName, Key *k);

    /// Restituisce il numero dei gruppi presenti in queste impostazioni
    Natural getGroupsCount();

    /// Aggiunge la chiave k al gruppo con l'indice group_index
    void addKey(Natural group_index, Key *k);

    /// Restituisce la chiave con quel nome nel gruppo group_name
    Key* getKey(QString group_name, QString key_name);

    /// Cerca una chiave con quel nome e la restituisce,
    /// se non esiste restituisce una chiave vuota
    Key* getKey(QString name);

    /// Determina se esiste una chiave con quel nome in tutti i gruppi
    bool existsKey(QString name);

    /// Determina se esiste la chiave name nel gruppo con quell' indirizzo
    bool existsKey(Natural group_index, QString name);

    /// Determina se esiste una chiave con quel nome nel gruppo con quel nome
    bool existsKey(QString group_name, QString name);

    /// Restituisce il valore della chiave con quel nome
    /// \arg group_name nome del gruppo in cui cercare
    QString getKeyValue(QString group_name, QString key_name);

    /// Imposta il valore della chiave con quel nome
    void setKeyValue(QString name, QString value);

    /// Cerca la chiave nel gruppo e ne imposta il valore
    void setKeyValue(QString group_name, QString key_name, QString value);
private:
    // Percorso del file
    QString file_path = "";

    // Lista con i gruppi
    QList<Group*> groups;
};

#endif // SETTINGS_H
