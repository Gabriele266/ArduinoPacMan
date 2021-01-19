#include "packagetab.h"
#include "ui_packagetab.h"

PackageTab::PackageTab(Package *package, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PackageTab)
{
    ui->setupUi(this);
    this->package = package;
}

void PackageTab::setTags(QString tags){
    tag = tags;
}

QString PackageTab::getTags(){
    return tag;
}

PackageTab::~PackageTab()
{
    delete ui;
}
