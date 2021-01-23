#include "attributeditem.h"

AttributedItem::AttributedItem()
{

}

void AttributedItem::addTag(QString tag){
    tags.append(tag);
}

bool AttributedItem::hasTag(QString tag){
    for(int x = 0; x < tags.count(); x ++){
        // Controllo se il tag corrente è uguale a quello da cercare
        if(tags[x] == tag){
            return true;
        }
    }
    return false;
}

void AttributedItem::setTag(Natural index, QString value){
    tags[index] = value;
}

void AttributedItem::addParameterTag(QString tagName, QString tagVal){
    tags.append("<" + tagName + " value=" + '"' + tagVal + '"' + ">");
}

void AttributedItem::clearTags(){
    tags.clear();
}

QStringList* AttributedItem::getTagsList(){
    return &tags;
}

QString AttributedItem::getTag(Natural index){
    return tags[index];
}
