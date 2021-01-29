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
