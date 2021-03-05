#include "nameditem.h"


NamedItem::NamedItem(QString name){
    this->name = name;
}

NamedItem::NamedItem() : NamedItem("")
{
    // Nulla
}

bool NamedItem::operator==(NamedItem &item){
    return hasSameName(item);
}

bool NamedItem::hasSameName(NamedItem &item){
    if(item.getName() == name){
        return true;
    }
    return false;
}
