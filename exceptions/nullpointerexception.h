#ifndef NULLPOINTEREXCEPTION_H
#define NULLPOINTEREXCEPTION_H

#include <QString>
#include <iostream>
#include "utils/macros.h"

#include "packages/natural.h"

using namespace std;

class NullPointerException : public exception
{
public:
    NullPointerException();
    NullPointerException(QString dataType, QString identifier, Natural line, QString file = __FILE__);

    QString toString();

    GETTER(QString, dataType, DataType);
    GETTER(QString, identifyer, Identifier);
    GETTER(Natural, line, Line);

private:
    QString dataType;
    QString identifyer;
    Natural line;
    QString function;
    QString file;
};

#endif // NULLPOINTEREXCEPTION_H
