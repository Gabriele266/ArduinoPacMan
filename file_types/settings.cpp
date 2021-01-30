#include "settings.h"

Settings::Settings()
{

}

void Settings::addGroup(Group *g){
    groups.append(g);
}

Group* Settings::getGroup(Natural index){
    return groups [index];
}

Group* Settings::getGroup(QString byName){
    // Scorro tutti i gruppi
    for(Natural x = 0; x < mk(groups.count()); x++){
        if(groups.at(x)->getName() == byName){
            return groups[x];
        }
    }
    return nullptr;
}

void Settings::addKey(QString groupName, Key *k){
    auto g = getGroup(groupName);
    // Controllo che esista un gruppo
    if(g != nullptr){
        g->addKey(k);
    }
}

Natural Settings::getGroupsCount(){
    return groups.count();
}

Key* Settings::getKey(QString group_name, QString key_name){
    auto g = getGroup(group_name);

    // Controllo che esista
    if(g != nullptr){
        return g->getKey(key_name);
    }
    else{
        return nullptr;
    }
}

Key* Settings::getKey(QString name){
    // Scorro tutti i gruppi
    for(Natural x = 0; x < mk(groups.count()); x++){
        Key* d = groups[x]->getKey(name);
        if(d != nullptr){
            return d;
        }
    }
    return nullptr;
}

QString Settings::getKeyValue(QString group_name, QString key_name){
    // Ottengo il gruppo con quel nome
    Group* gr = getGroup(group_name);

    if(gr != nullptr){
        auto k = gr->getKey(key_name);

        if(k != nullptr){
            return k->getValue();
        }
    }
    return "";
}

void Settings::setKeyValue(QString name, QString value){
    auto key = getKey(name);
    if(key != nullptr){
        key->setValue(value);
    }
}

void Settings::setKeyValue(QString group_name, QString key_name, QString value){
    // Rintraccio la chiave
    auto key = getKey(group_name, key_name);

    if(key != nullptr){
        key->setValue(value);
    }
}

bool Settings::existsKey(QString name){
    for(Natural x = 0; x < mk(groups.count()); x++){
        Key* d = groups[x]->getKey(name);
        if(d != nullptr){
            return true;
        }
    }
    return false;
}

bool Settings::existsKey(Natural group_index, QString name){
    if(groups[group_index]->getKey(name) != nullptr){
        return true;
    }
    return false;
}

bool Settings::existsKey(QString group_name, QString key_name){
    // Gruppo con quel nome
    auto g = getGroup(group_name);
    // Controllo se esiste
    if(g != nullptr){
        if(g->getKey(key_name) != nullptr){
            return true;
        }
    }
    return false;
}
