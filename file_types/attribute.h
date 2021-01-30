/*  Autore: cavallo gabriele
 *
 *  Rappresenta un attributo in una chiave
 * */

#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QString>
#include <QList>

#include "utils/macros.h"



/// Rappresenta un attributo in una chiave
class Attribute
{
public:
    Attribute();
    Attribute(QString name, QString value);

    GETTER_SETTERC(QString, name, Name,
                   Imposta il nome dell attributo,
                   Restituisce il nome dell attributo)

    GETTER_SETTERC(QString, value, Value,
                   Imposta il valore dell attributo,
                   Restituisce il valore dell attributo)

    bool operator==(Attribute a);
private:
    // Nome dell' attributo
    QString name;
    // Valore dell' attributo
    QString value;
};

/// Rappresenta una lista di attributi
class AttributeList : public QList<Attribute*>{
public:
    AttributeList(){
        // Niente
    }

    AttributeList(Attribute* attr){
        append(attr);
    }
};

#endif // ATTRIBUTE_H
