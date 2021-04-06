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

    try{
        // Load the file
        FileLoader *loader = new FileLoader();
        loader->setFilePath(formatPathForOs(getCurrentPath(), QStringList("info.html")));
        // Avvio il caricamento
        loader->start();

        // Wait file loading
        while(loader->isRunning()){}

        // Get the buffer and set it to the content of the text browser
        ui->newsInfoBrowser->setHtml(loader->getFileBuffer());

        // Delete the loader
        delete loader;
    }catch(FileNotFoundException &i){
        qInfo() << i.toString();
        QMessageBox::critical(this, "Error", i.toString());
    }

    // Imposto le informazioni per riconoscere il tab
    setName("Home");
    setInfo("<home>");
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
