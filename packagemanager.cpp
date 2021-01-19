#include "packagemanager.h"

PackageManager::PackageManager()
{

}

void PackageManager::setUiElement(QTabWidget *manager) {
    widget_manager = manager;
}

void PackageManager::addPackage(Package *pack,bool is_new, bool show){
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
        PackageTab newTab(pack);

        // Aggiungo il tab
        widget_manager->addTab(&newTab, pack->getName());
    }
}
