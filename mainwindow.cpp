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
}

void MainWindow::updateTitleInfo(){

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
        package->create();

        // Aggiungo il pacchetto al gestore
        packageManager->addPackage(package);
    }
}

void MainWindow::on_packageManager_currentChanged(int index)
{
    // Aggiorno il titolo
    updateTitleInfo();
}
