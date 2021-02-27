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

QString Group::getValue(QString key_name){
    // Ottengo la chiave con quel nome
    Key* k = getKey(key_name);
    if(k != nullptr){
        return k->getValue();
    }
    return "";
}

Natural Group::getKeysCount(){
    return mk(keys.count());
}
