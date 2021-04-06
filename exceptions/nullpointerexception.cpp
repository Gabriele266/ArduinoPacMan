#include "nullpointerexception.h"

NullPointerException::NullPointerException()
{
    this->dataType = "";
    this->line = __LINE__;
    this->identifyer = "";
    this->file = __FILE__;
}

NullPointerException::NullPointerException(QString dataType, QString
                                           identifier, Natural line, QString file){
    this->dataType = dataType;
    this->line = line;
    this->identifyer = identifier;
    this->file = file;
}

QString NullPointerException::toString(){
    return "NullPointerException: A null pointer was called. Data type: " + dataType +
            "\nIdentityer: " + identifyer + "\nLine: " + line.toString();
}
