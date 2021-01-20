#include "packagemanager.h"

PackageManager::PackageManager()
{

}

void PackageManager::setUiElement(QTabWidget *manager) {
    widget_manager = manager;
}

void PackageManager::addPackage(Package *pack, bool is_new, bool show){
    // Controllo che non sia un puntatore nullo
    if(pack != nullptr){
        // Aggiungo il pacchetto
        packages.append(pack);
        // Controllo se il paccketto è nuovo
        if(is_new){
            // Creo il pacchetto
            pack->create();
        }
        // Aggiungo il tab
        PackageTab *newTab = new PackageTab(pack);

        // Aggiungo il tab
        widget_manager->addTab(newTab, pack->getName());
    }
}

unsigned int PackageManager::getOpenedPackages(){
    return packages.count();
}

bool PackageManager::searchTab(QString str){
    for(int x = 0; x < widget_manager->count(); x++){
        if(widget_manager->tabText(x) == str){
            return true;
        }
    }
    return false;
}

unsigned int PackageManager::getHomeIndexIfExists(){
    // Scorro tutti i tab
    for(int x = 0; x < widget_manager->count(); x++){
        QString curTabText = widget_manager->tabText(x);

        if(curTabText.compare(curTabText, "home", Qt::CaseInsensitive)){
            return x;
        }
    }
    return -1;
}

bool PackageManager::isHomeCurrent(){
    return (unsigned int) widget_manager->currentIndex() == (getHomeIndexIfExists() - 1);
}

Package* PackageManager::getCurrentPackage(){
    // Controllo se la scheda corrente è la home
    if(isHomeCurrent()){
        return nullptr;
    }
    else{
        qInfo() << "Non siamo nella home \n";
        return packages[widget_manager->currentIndex() - 1];
    }
}
