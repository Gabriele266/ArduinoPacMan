#include "attribute.h"

Attribute::Attribute()
{

}

Attribute::Attribute(QString name, QString value){
    this->name = name;
    this->value = value;
}

bool Attribute::operator==(Attribute a){
    if(name == a.getName() && value == a.getValue()){
        return true;
    }
    return false;
}
