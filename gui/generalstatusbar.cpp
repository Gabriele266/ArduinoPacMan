#include "generalstatusbar.h"
#include "ui_generalstatusbar.h"

GeneralStatusBar::GeneralStatusBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralStatusBar)
{
    ui->setupUi(this);
}

void GeneralStatusBar::setLibraryCount(Natural count){
    ui->librariesCount->setText(QString("%1 librerie").arg(count));
}

void GeneralStatusBar::setPackagesCount(Natural val){
    ui->openedPackages->setText(QString("%1 pacchetti").arg(val));
}

void GeneralStatusBar::setCurrentPackagePath(QString path){
    ui->packagePath->setText(path);
}

void GeneralStatusBar::hideLibrariesCount(){
    ui->librariesCount->setVisible(false);
}

void GeneralStatusBar::hidePackagesCount(){
    ui->openedPackages->setVisible(false);
}

void GeneralStatusBar::showLibrariesCount(){
    ui->librariesCount->setVisible(true);
}

void GeneralStatusBar::showPackagesCount(){
    ui->openedPackages->setVisible(true);
}

GeneralStatusBar::~GeneralStatusBar()
{
    delete ui;
}
