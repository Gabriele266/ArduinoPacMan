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

    // Scrivo il percorso in uso per il salvataggio dei percorsi di ricerca librerie
    qInfo() << "File percorsi di ricerca librerie: " << libSearchPath << endl;

    // Avvio la lettura per i percorsi di ricerca lib
    SearchPathListReader *reader = new SearchPathListReader();
    reader->setDestinationList(&librariesSearchPath);
    librariesSearchPath.setSavePath(libSearchPath);
    reader->setFile(libSearchPath);

    reader->start();

    // Controllo se ci sono delle impostazioni
    if(application_settings != nullptr){
        // Applico le impostazioni
    }
    else{
        // Scrivo le impostazioni base
        writeDefaultSettings();
    }

    readDefaultSettings();
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
        // Imposto le generalità
        package->setName(dialog->getPackageName());
        package->setSavePath(dialog->getPackagePath());

        // Imposto i percorsi legati ai sorgenti del progetto
        package->setSourcesPath(dialog->getSourcesPath());
        package->setMainSourcePath(dialog->getMainFilePath());

        // Imposto la descrizione del pacchetto
        package->setDescription(dialog->getDescription());

        // Imposto la data e l'ora di creazione del pacchetto
        package->setCreationDate(QDate::currentDate());
        package->setCreationTime(QTime::currentTime());

        // Imposto l'orario di ultima modifica
        package->setLastModifyDate(QDate::currentDate());
        package->setLastModifyTime(QTime::currentTime());

        qInfo() << " descrizione " << dialog->getDescription() << endl;
        package->create();

        // Aggiungo il pacchetto al gestore
        packageManager->addPackage(package);
    }

    // Aggiorno il titolo
    updateTitleInfo();
    // Aggiorno la barra di stato
    updateStatusBar();
}

void MainWindow::aggiungiPercorsoRicercaTriggered(QString path){
    librariesSearchPath.addPath(path);
    qInfo() << "Aggiunto percorso " << path << endl;
}

void MainWindow::on_packageManager_currentChanged(int index)
{
    // Aggiorno il titolo
    updateTitleInfo();
}

void MainWindow::rimuoviPercorsoRicerca(QString path){
    // Rimuovo l'elemento con quel testo
    librariesSearchPath.removeElemByPath(path);
}

void MainWindow::modificaPercorsoRicerca(Natural index, QString old_val, QString new_val){
    librariesSearchPath.editElem(index, new_val);
    qInfo() << "Valore " << new_val << " nuovo per " << old_val << " con indice " << index << endl;
}

void MainWindow::on_actionPercorsi_ricerca_librerie_triggered()
{
    // Creo la finestra
    SearchPathManager *man = new SearchPathManager();

    // Connetto il segnale di aggiunta di una nuova entry el metodo di gestione
    QObject::connect(man, &SearchPathManager::pathAdded, this, &MainWindow::aggiungiPercorsoRicercaTriggered);

    // Connetto il segnale di rimozione degli elementi
    QObject::connect(man, &SearchPathManager::pathRemoved, this, &MainWindow::rimuoviPercorsoRicerca);

    // Connetto il segnale per la modifica degli elementi
    QObject::connect(man, &SearchPathManager::pathEdited, this, &MainWindow::modificaPercorsoRicerca);

    // Controllo se sono presenti dei percorsi già salvati
    if(librariesSearchPath.getListCount() > 0){
        man->loadFromList(librariesSearchPath.getEntryList());
    }

    int res = man->exec();

    // Controllo se l'utente ha accettato
    if(res == QDialog::Accepted){
        // Avvio uno scrittore
        SearchPathListWriter *writer = new SearchPathListWriter();
        writer->setLibraryList(&librariesSearchPath);

        // Avvio il thread di scrittura
        writer->start();
    }
}

void MainWindow::on_actionApri_pacchetto_triggered()
{
    // Chiedo una directory in cui cercare il pacchetto
    QString dir = QFileDialog::getExistingDirectory(this, "Selezionare la cartella del pacchetto");

    // Controllo che l'utente abbia accettato
    if(dir != ""){
        // Avvio un thread di lettura delle informazioni sul pacchetto
        PackageReader *reader = new PackageReader();
        reader->setPath(dir);

        reader->start();

        // Attendo che finisca
        while(reader->isRunning()){
            // Attendo
        }
        // Aggiungo il pacchetto
        packageManager->addPackage(reader->getPackage());
    }
}
