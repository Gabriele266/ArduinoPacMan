#include "packagetab.h"
#include "ui_packagetab.h"

PackageTab::PackageTab(Package *package, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PackageTab)
{
    ui->setupUi(this);
    this->package = package;
}

PackageTab::~PackageTab()
{
    delete ui;
}
