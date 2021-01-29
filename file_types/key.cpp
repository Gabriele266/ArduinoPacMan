#include "key.h"

Key::Key(QString n, QString val){
    name = n;
    value = val;
}

Key::Key() : Key("", "")
{
    // Niente
}

bool Key::loadFromString(QDomElement str){
    // Prendo il nome dell' elemento
    name = str.tagName();
    // Prendo il valore
    value = str.attribute("value");

    auto attributes = str.attributes();

    // Scorro tutti gli attributi
    for(Natural x = 0; x < mk(attributes.count()); x++){
        // Ottengo l'oggetto attributo per l'elemento
        auto i = attributes.item(x).toAttr();
        QString n = i.name();
        QString v = i.value();

        // Aggiungo l'elemento
        additional_attributes.insert(n, v);
    }
    return true;
}

Natural Key::getAttributesCount(){
    return additional_attributes.count();
}

Key Key::keyFromElement(QDomElement element){
    Key k;
    k.setName(element.tagName());
    k.setValue(element.attribute("value"));

    auto attributes = element.attributes();

    // Scorro tutti gli attributi
    for(Natural x = 0; x < mk(attributes.count()); x++){
        // Ottengo l'oggetto attributo per l'elemento
        auto i = attributes.item(x).toAttr();
        QString n = i.name();
        QString v = i.value();

        k.addAttribute(n, v);
    }
    return k;
}

void Key::addAttribute(QString name, QString value){
    additional_attributes.insert(name, value);
}

void Key::addAttribute(QMap<QString, QString> map){
    additional_attributes.insert(map);
}

QString Key::getAttribute(QString name){
    return additional_attributes[name];
}

QDomElement Key::getElement(){
    QDomElement elem;
    elem.setTagName(name);
    elem.setAttribute("value", value);

    // Itero gli elementi
    QMap<QString, QString>::iterator i;
    for(i = additional_attributes.begin(); i != additional_attributes.end(); i++){
        // aggiungo l'elemento
        elem.setAttribute(i.key(), i.value());
    }

    return elem;
}
