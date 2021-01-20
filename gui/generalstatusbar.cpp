#include "generalstatusbar.h"
#include "ui_generalstatusbar.h"

GeneralStatusBar::GeneralStatusBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GeneralStatusBar)
{
    ui->setupUi(this);
}

void GeneralStatusBar::setLibraryCount(unsigned int count){
    ui->librariesCount->setText(QString("%1 librerie").arg(count));
}

void GeneralStatusBar::setPackagesCount(unsigned int val){
    ui->openedPackages->setText(QString("%1 pacchetti").arg(val));
}

void GeneralStatusBar::setCurrentPackagePath(QString path){
    ui->packagePath->setText(path);
}

GeneralStatusBar::~GeneralStatusBar()
{
    delete ui;
}
