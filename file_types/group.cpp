#include "group.h"

Group::Group()
{

}

void Group::addKey(Key *k){
    keys.append(k);
}

Key* Group::getKey(Natural index){
    if(keys.count() > mk(index)){
            return keys.at(index);
    }
    else{
        return new Key();
    }
}

Key* Group::getKey(QString name){
    for(Natural x = 0; x < mk(keys.count()); x++){
        if(keys[x]->getName() == name){
            return keys[x];
        }
    }
    return nullptr;
}

QDomElement Group::toElement(){
    QDomElement el;
    el.setTagName(name);
    for(Natural x = 0; x < mk(keys.count()); x++){
        el.appendChild(keys.at(x)->getElement());
    }
    return el;
}

Natural Group::getKeysCount(){
    return mk(keys.count());
}
