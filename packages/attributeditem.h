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

/// Rappresenta un oggetto con degli attributi
class AttributedItem
{
public:
    AttributedItem();

    /// Imposta il nome dell' oggetto
    void setName(QString name);

    /// Imposta l'autore dell' oggetto
    void setAuthor(QString author);

    /// Imposta la data di creazione
    void setCreationDate(QDate date);
    void setCreationDate(QString date);

    /// Imposta l'orario di creazione dell' oggetto
    void setCreationTime(QTime time);
    void setCreationTime(QString str);

    /// Imposta l'orario di ultima modifica dell' oggetto
    void setLastModifyTime(QString time);
    void setLastModifyTime(QTime time);

    /// Imposta la data di ultima modifica dell' oggetto
    void setLastModifyDate(QDate date);
    void setLastModifyDate(QString date);

    /// Imposta la descrizione a partire da una stringa
    void setDescription(QString description);

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

    /// Restituisce il nome
    QString getName();

    /// Restituisce l'autore
    QString getAuthor();

    /// Restituisce la data di creazione
    QDate getCreationDate();
    QString getCreationDateString();

    QTime getCreationTime();
    QString getCreationTimeString();

    QDate getLastModifyDate();
    QString getLastModifyDateString();

    QTime getLastModifyTime();
    QString getLastModifyTimeString();

    QString getLastModifyInfo();

    /// Restituisce la descrizione dell' oggetto
    QString getDescription();

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
