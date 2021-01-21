#include "attributeditem.h"

AttributedItem::AttributedItem()
{

}

void AttributedItem::setAuthor(QString author){
    this->author = author;
}

void AttributedItem::setCreationDate(QDate date){
    creation_date = date;
}

void AttributedItem::setCreationDate(QString date){
    creation_date = QDate::fromString(date);
}

void AttributedItem::setCreationTime(QTime time){
    creation_time = time;
}

void AttributedItem::setCreationTime(QString str){
    creation_time = QTime::fromString(str);
}

void AttributedItem::setDescription(QString description){
    this->description = description;
}

void AttributedItem::setLastModifyDate(QDate date){
    last_modify_date = date;
}

void AttributedItem::setLastModifyDate(QString date){
    last_modify_date = QDate::fromString(date);
}

void AttributedItem::setLastModifyTime(QString time){
    last_modify_time = QTime::fromString(time);
}

void AttributedItem::setLastModifyTime(QTime time){
    last_modify_time = time;
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

QString AttributedItem::getAuthor(){
    return author;
}

QString AttributedItem::getName(){
    return name;
}

QDate AttributedItem::getCreationDate(){
    return creation_date;
}

QString AttributedItem::getCreationDateString(){
    return creation_date.toString();
}

QTime AttributedItem::getCreationTime(){
    return creation_time;
}

QString AttributedItem::getCreationTimeString(){
    return creation_time.toString();
}

QDate AttributedItem::getLastModifyDate(){
    return last_modify_date;
}

QString AttributedItem::getLastModifyDateString(){
    return last_modify_date.toString();
}

QTime AttributedItem::getLastModifyTime(){
    return last_modify_time;
}

QString AttributedItem::getLastModifyTimeString(){
    return last_modify_time.toString();
}

QString AttributedItem::getLastModifyInfo(){
    return getLastModifyDateString() + " " + getLastModifyTimeString();
}

QString AttributedItem::getDescription(){
    return description;
}

QStringList* AttributedItem::getTagsList(){
    return &tags;
}

QString AttributedItem::getTag(Natural index){
    return tags[index];
}
