#include "packagemanager.h"
#include "ui_packagemanager.h"

PackageManager::PackageManager()
{

}

PackageTab* PackageManager::addPackage(Package *pack){
    // Controllo che non sia un puntatore nullo
    if(pack != nullptr){
        // Imposto l'indice del pacchetto
        pack->addTag(QString::number(packages.count()));
        // Aggiungo il pacchetto
        packages.append(pack);

        // Mostro il pacchetto
        PackageTab *tab = new PackageTab(pack);
        // Imposto i tag del tab
        tab->setTags("<package>");
        // Aggiungo
        tabWidget->addTab(tab, pack->getName());

        // Carico i suoi sorgenti
        auto *loader = new SourcesLoader();
        loader->setDestination(tab->getFileBrowser());
        loader->setSearchPath(pack->getSourcesPath());
        loader->setPackage(pack);

        // Avvio il thread
        loader->start(QThread::HighPriority);

        lister = new SrcDependencyLister();
        // Imposto il pacchetto
        lister->setPackage(pack);
        // Imposto il widget
        lister->setWidget(tab->getDependencyBrowser());
        lister->start();

        return tab;
    }
    return nullptr;
}

bool PackageManager::isCurrentPackage(){
    // Indice del tab corrente
    int cur = tabWidget->currentIndex();

    // Scorro tutti i pacchetti e controllo i loro tag per sapere se si tratta di un tab-pacchetto
    for(int x = 0; x < packages.count(); x++){
        if(packages[x]->getTag(0).toInt() == cur){
            return true;
        }
    }
    return false;
}

void PackageManager::startDependencyIndexer(Package *package, QTreeWidget* widget){
    // Creo il thread

}

Package* PackageManager::getCurrentPackage(){
    // Determino se il tab corrente è un pacchetto
    // Prendo l'indice corrente
    int current = tabWidget->currentIndex();

    // Scorro tutti i pacchetti e controllo i loro tag per sapere se si tratta di un tab-pacchetto
    for(int x = 0; x < packages.count(); x++){
        if(packages[x]->getTag(0).toInt() == current){
            return packages[x];
        }
    }
    return nullptr;
}

unsigned int PackageManager::getPackagesCount(){
    return packages.count();
}

bool PackageManager::hasPackages(){
    return getPackagesCount() != 0;
}

unsigned int PackageManager::getCurrentPackageIndex(){
    // Controllo se il tab corrente è un pacchetto
    if(isCurrentPackage()){
        return 0;
    }
}

void PackageManager::init(){

}
