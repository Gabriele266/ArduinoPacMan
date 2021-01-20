#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Aggiungo il widget per la gestione dei pacchetti
    ui->verticalLayout->addWidget(packageManager);

    // Inizializzo il gestore dei pacchetti
    packageManager->init();

    // Imposto la barra di stato
    ui->statusbar->addPermanentWidget(statusBar, 1);

    // Aggiorno il titolo
    updateTitleInfo();

    // Connetto il segnale di cambiamento dei tab
    QObject::connect(packageManager, &PackageManager::tabChanged, this, &MainWindow::onPackageManagerTabChange);

}

void MainWindow::updateTitleInfo(){
    // Titolo base
    QString title = QString("ArduinoPacMan %1 ").arg(ARDUINO_PACMAN_VERSION.toString());
    // Controllo se ci sono dei pacchetti aggiunti
    if(packageManager->hasPackages()){
        // Determino se il tab corrente è un pacchetto
        if(packageManager->isCurrentPackage()){
            // Scrivo il nome del pacchetto
            title += "| ";
            title += packageManager->getCurrentPackage()->getName();
        }
    }
    setWindowTitle(title);
}

void MainWindow::onPackageManagerTabChange(unsigned int newTab){
    updateTitleInfo();
    updateStatusBar();
}

void MainWindow::updateStatusBar(){
    // Scrivo il numero di pacchetti aperti
    statusBar->setPackagesCount(packageManager->getPackagesCount());

    // Controllo se ci sono pacchetti presenti
    if(packageManager->isCurrentPackage()){
        // Imposto il percorso del pacchetto corrente
        statusBar->setCurrentPackagePath(packageManager->getCurrentPackage()->getSavePath());
        statusBar->setLibraryCount(packageManager->getCurrentPackage()->getLibraryCount());
    }
    else{
        statusBar->setCurrentPackagePath("Scheda home");
        statusBar->setLibraryCount(0);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNuova_finestra_triggered()
{
    // Creo una nuova finestra
    MainWindow *mainWin = new MainWindow();
    mainWin->show();
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_actionNuovo_pacchetto_triggered()
{
    NewPackageDialog *dialog = new NewPackageDialog();
    int res = dialog->exec();

    if(res == QDialog::Accepted){
        Package *package = new Package();
        package->setName(dialog->getPackageName());
        package->setSavePath(dialog->getPackagePath());
        package->setSourcesPath(dialog->getSourcesPath());
        package->setMainFilePath(dialog->getMainFilePath());
        package->create();

        // Aggiungo il pacchetto al gestore
        packageManager->addPackage(package);
    }

    // Aggiorno il titolo
    updateTitleInfo();
    // Aggiorno la barra di stato
    updateStatusBar();
}

void MainWindow::on_packageManager_currentChanged(int index)
{
    // Aggiorno il titolo
    updateTitleInfo();
}
