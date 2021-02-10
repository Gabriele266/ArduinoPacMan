#include "homepage.h"
#include "ui_homepage.h"

HomePage::HomePage(QStringList *recentFiles, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);

    if(recentFiles != nullptr){
        for(int x = 0; x < recentFiles->count(); x++){
            QListWidgetItem *item = new QListWidgetItem();
            item->setIcon(QIcon(":/icons/program/Information.png"));
            item->setText(recentFiles->at(x));
            ui->recentsView->addItem(item);
        }
    }
    else{
        ui->recentsView->addItem("Nessun file recente... Mi sa che dovrai crearne uno nuovo!!");
    }

    // Carico il file
    FileLoader *loader = new FileLoader();
    loader->setBrowser(ui->newsInfoBrowser);
    loader->setFilePath(formatPathForOs(getCurrentPath(), QStringList("info.html")));
    // Avvio il caricamento
    loader->start();
}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::on_newPackage_clicked()
{
    emit newPackageRequired();
}

void HomePage::on_openPackage_clicked()
{
    emit openPackageRequired();
}
