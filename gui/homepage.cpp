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
    loader->setFilePath(formatPathForOs(getCurrentPath(), QStringList("info.html")));
    // Avvio il caricamento
    loader->start();

    // Check if it was successful
    while(loader->isRunning()){
    }

    if(loader->wasSuccessful()){
        // Get the buffer and set it to the content of the text browser
        ui->newsInfoBrowser->setHtml(loader->getFileBuffer());
    }
    else{
        // Read the exit state
        auto exit_state = loader->getExitState();
        // Send notification
        QMessageBox::critical(this, "Errore", "Errore nella apertura del file per le news di ArduinoPacMan \n. Testo dell' errore: " +
                              loader->getErrorString() + " tipologia di eccezione: " + FileLoader::exitStateToString(exit_state) + "\n"
        "File richiesto: " + loader->getFilePath());
    }

    // Delete the loader
    delete loader;

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
