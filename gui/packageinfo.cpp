#include "packageinfo.h"
#include "ui_packageinfo.h"

PackageInfo::PackageInfo(Package* p, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PackageInfo)
{
    ui->setupUi(this);

    this->package = p;

    loadPackage(package);
}

PackageInfo::~PackageInfo()
{
    delete ui;
}

void PackageInfo::loadPackage(Package* pack){
    // Controllo che il pacchetto esista in memoria
    if(pack != nullptr){
        setWindowTitle(QString("Informazioni pacchetto ") + pack->getName());
        ui->packageName->setText(pack->getName());
        ui->packageCompletePath->setText(pack->getCompletePath());
        ui->packageDescription->setHtml(pack->getDescription());
        ui->packageSourcesPath->setText(pack->getSourcesPath());
        ui->packageMainFile->setText(pack->getMainSourcePath());
        ui->creationDate->setText(pack->getCreationDate().toString());
        ui->creationTime->setText(pack->getCreationTime().toString());
        ui->lastModifyDate->setText(pack->getLastModifyDate().toString());
        ui->lastModifyTime->setText(pack->getLastModifyTime().toString());
    }
}
