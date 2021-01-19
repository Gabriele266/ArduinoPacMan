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
        pack->setTags(QString::number(packages.count() - 1));
        // Aggiungo il pacchetto
        packages.append(pack);

        // Mostro il pacchetto
        PackageTab *tab = new PackageTab(pack);
        // Imposto i tag del tab
        tab->setTags("<package>");
        // Aggiungo
        ui->surfaceManager->addTab(tab, pack->getName());
    }
}

bool PackageManager::isCurrentPackage(){
    // Indice del tab corrente
    int cur = ui->surfaceManager->currentIndex();
    if(cur >= 0){
        auto tab = static_cast<PackageTab*>( ui->surfaceManager->widget(cur));
        qInfo() << "Tags: " << tab->getTags();
        // Controllo il suo tag
        if(tab->getTags() == "<package>"){
            // Si tratta di un pacchetto
            return true;
        }
        return false;
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
}
