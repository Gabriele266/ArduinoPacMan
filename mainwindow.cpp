#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Rimuovo il secondo tab
    ui->packageManager->removeTab(1);

    manager.setUiElement(ui->packageManager);
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

        manager.addPackage(package);
    }
}
