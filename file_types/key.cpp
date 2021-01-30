#include "key.h"

Key::Key(QString n, QString val){
    name = n;
    value = val;
    attributes ;
}

Key::Key() : Key("", "")
{
    // Niente
}

Key::Key(QString name, QString value, AttributeList attributes) : Key(name, value){
    this->attributes = attributes;
}

Natural Key::getAttributesCount(){
    return attributes.count();
}

void Key::addAttribute(QString name, QString value){
    attributes.append(new Attribute(name, value));
}

void Key::addAttribute(Attribute *attr){
    attributes.append(attr);
}

Attribute* Key::getAttributeByName(QString name){
    // Scorro tutti gli attributi
    for(Natural x = 0; x < mk(attributes.count()); x++){
        auto curr = attributes[x];
        if(curr->getName() == name){
            return curr;
        }
    }
    return new Attribute();
}

Attribute* Key::getAttributeByIndex(Natural index){
    if(index < mk(attributes.count())){
        return attributes[index];
    }
    return nullptr;
}

void Key::setAttributeValue(QString attribute_name, QString value){
    auto attr = getAttributeByName(attribute_name);
    attr->setValue(value);
}

QString Key::getAttributeValue(QString attribute_name){
    auto attr = getAttributeByName(attribute_name);
    if(attr != nullptr){
        return attr->getValue();
    }
    return "";
}
