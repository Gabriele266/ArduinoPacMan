/* Rappresenta un oggetto con degli attributi
 *
 * */

#ifndef ATTRIBUTEDITEM_H
#define ATTRIBUTEDITEM_H

#include <QString>
#include <QDate>
#include <QStringList>
#include <QTime>
#include <QFile>
#include <QTextStream>

#include "natural.h"
#include "../utils/macros.h"

/// Rappresenta un oggetto con degli attributi
class AttributedItem
{
public:
    AttributedItem();

    /// Imposta il nome dell' oggetto
    GETTER_SETTER(QString, name, Name)

    GETTER_SETTER(QString, author, Author)

    GETTER_SETTER(QDate, creation_date, CreationDate)

    /// Permette di impostare la data di creazione tramite l'uso di una stringa
    CUSTOM_SETTER(QString, creation_date, CreationDate, QDate::fromString(mem))

    GETTER_SETTER(QTime, creation_time, CreationTime)

    /// Permette di impostare l'orario di creazione tramite una stringa
    CUSTOM_SETTER(QString, creation_time, CreationTime, QTime::fromString(mem))

    GETTER_SETTER(QDate, last_modify_date, LastModifyDate)

    CUSTOM_SETTER(QString, last_modify_date, LastModifyDate, QDate::fromString(mem))

    GETTER_SETTER(QTime, last_modify_time, LastModifyTime)

    CUSTOM_SETTER(QString, last_modify_time, LastModifyTime, QTime::fromString(mem))

    GETTER_SETTER(QString, description, Description)

    /// Imposta la descrizione a partire da un file
    void loadDescription(QFile file);

    /// Aggiunge un tag
    void addTag(QString tag);

    /// Imposta il tag con quell' indice
    void setTag(Natural index, QString value);

    /// Determina se è presente questo tag
    bool hasTag(QString tag);

    /// Aggiunge un tag parametrico
    void addParameterTag(QString tagName, QString tagVal);

    /// Pulisce i tag
    void clearTags();

    /// Restituisce la data di creazione
    CUSTOM_GETTER(QString, creation_date, CreationDateString, creation_date.toString())

    CUSTOM_GETTER(QString, creation_time, CreationTimeString, creation_time.toString())

    CUSTOM_GETTER(QString, last_modify_date, LastModifyDateString, last_modify_date.toString())

    CUSTOM_GETTER(QString, last_modify_time, LastModifyTimeString, last_modify_time.toString())

    QString getLastModifyInfo();

    QStringList* getTagsList();

    /// Restituisce il tag con quell' indirizzo
    QString getTag(Natural index);

private:
    // Nome dell' oggetto
    QString name;
    // Autore dell' oggetto
    QString author;
    // Data di creazione
    QDate creation_date;
    // Orario di creazione
    QTime creation_time;

    // Data di ultima modifica
    QDate last_modify_date;
    // Orario di ultima modifica
    QTime last_modify_time;

    // Descrizione dell' oggetto
    QString description;
    // Tag dell' oggetto
    QStringList tags;
};

#endif // ATTRIBUTEDITEM_H
