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

PackageManager::~PackageManager()
{
    delete ui;
}

void PackageManager::on_surfaceManager_currentChanged(int index)
{
    qInfo() << "Cambiato tab in package manager. \n";
}
