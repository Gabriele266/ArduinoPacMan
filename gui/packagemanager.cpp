#include "packagemanager.h"
#include "ui_packagemanager.h"

PackageManager::PackageManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PackageManager)
{
    ui->setupUi(this);
}

void PackageManager::addPackage(Package *pack){
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
        ui->surfaceManager->addTab(tab, pack->getName());

        // Carico i suoi sorgenti
        auto *loader = new SourcesLoader();
        loader->setDestination(tab->getFileBrowser());
        loader->setSearchPath(pack->getSourcesPath());

        // Avvio il thread
        loader->start(QThread::HighPriority);
        // Avvio il thread per il caricamento delle dipendenze
        startDependencyIndexer(pack);
    }
}

bool PackageManager::isCurrentPackage(){
    // Indice del tab corrente
    int cur = ui->surfaceManager->currentIndex();

    // Scorro tutti i pacchetti e controllo i loro tag per sapere se si tratta di un tab-pacchetto
    for(int x = 0; x < packages.count(); x++){
        if(packages[x]->getTag(0).toInt() == cur){
            return true;
        }
    }
    return false;
}

void PackageManager::startDependencyIndexer(Package *package){
    // Creo il thread
    SourcesLister *lister = new SourcesLister();

    lister->setMainFile(package->getMainFilePath());
    lister->setDestinationList(package->getDependenciesList());
    lister->start();
}

Package* PackageManager::getCurrentPackage(){
    // Determino se il tab corrente è un pacchetto
    // Prendo l'indice corrente
    int current = ui->surfaceManager->currentIndex();

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

    }
}

void PackageManager::init(){
    // Tolgo tutti i tab
    ui->surfaceManager->clear();
}

PackageManager::~PackageManager()
{
    delete ui;
}

void PackageManager::on_surfaceManager_currentChanged(int index)
{
    qInfo() << "Cambiato tab in package manager. \n";
    qInfo() << "Tab corrente è un pacchetto?: " << isCurrentPackage();

    // Emetto il segnale di cambio tab
    emit tabChanged(index);
}
