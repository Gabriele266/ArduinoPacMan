#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setTabWidget(ui->widgetManager);

    ui->widgetManager->clear();
    // Avvio la lettura delle impostazioni dal disco
    settings.setFilePath(formatPathForOs(QDir::currentPath(), QStringList("settings/settings.stc")));
    // Controllo se il file di impostazioni esiste
    if(QFile::exists(settings.getFilePath())){
        // Notifico che ho trovato le impostazioni
        qInfo() << "File di impostazioni esistente, avvio il caricamento. " << endl;
        // Avvio la lettura delle impostazioni
        SettingsReader *settingsReader = new SettingsReader();
        settingsReader->setSettingsObject(&settings);
        settingsReader->start();
    }
    else{
        qInfo() << "File di impostazioni non trovato, avvio la scrittura sul disco. " << endl;
        // Avvio la scrittura delle impostazioni
        writeDefaultSettings(&settings);
    }

    // Imposto la barra di stato
    ui->statusbar->addPermanentWidget(statusBar, 1);

    // Aggiorno il titolo
    updateTitleInfo();

    showHomePage();
}

void MainWindow::showHomePage(){
    // Aggiungo il tab home
    HomePage *home = new HomePage( nullptr);
    ui->widgetManager->addTab(home, "Home");

    // Connetto gli eventi
    QObject::connect(home, &HomePage::newPackageRequired, this, &MainWindow::onNewPackageRequired);
    QObject::connect(home, &HomePage::openPackageRequired, this, &MainWindow::onOpenPackageRequired);
}

void MainWindow::onNewPackageRequired(){
    qInfo() << "Nuovo pacchetto richiesto da un tab. " << endl;
    newPackage();
}

void MainWindow::onOpenPackageRequired(){
    openPackage();
}

void MainWindow::openPackage(){
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
        addPackage(reader->getPackage());
    }
}

void MainWindow::updateTitleInfo(){
    // Titolo base
    QString title = QString("ArduinoPacMan %1 ").arg(ARDUINO_PACMAN_VERSION.toString());
    // Controllo se ci sono dei pacchetti aggiunti
    if(hasPackages()){
        // Determino se il tab corrente è un pacchetto
        if(isCurrentPackage()){
            // Scrivo il nome del pacchetto
            title += "| ";
            title += getCurrentPackage()->getName();
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
    statusBar->setPackagesCount(getPackagesCount());

    // Controllo se ci sono pacchetti presenti
    if(isCurrentPackage()){
        // Imposto il percorso del pacchetto corrente
        statusBar->setCurrentPackagePath(getCurrentPackage()->getSavePath());
        statusBar->setLibraryCount(getCurrentPackage()->getLibraryCount());
    }
    else{
        statusBar->setCurrentPackagePath("Scheda home");
        statusBar->setLibraryCount(0);
    }
}

void MainWindow::newPackage(){
    NewPackageDialog *dialog = new NewPackageDialog(&settings);
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
        addPackage(package);
    }

    // Aggiorno il titolo
    updateTitleInfo();
    // Aggiorno la barra di stato
    updateStatusBar();
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
    newPackage();
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
    // Pulisco la lista degli elementi
    librariesSearchPath.clear();

    // Avvio il caricamento dei percorsi di ricerca dal percorso specificato nelle impostazioni
    SearchPathListReader *reader = new SearchPathListReader();
    // Formatto il percorso su cui leggere o scrivere le informazioni
    QString use_path = resolvePath(settings.getKeyValue("paths", "libsearchpath"));
    // Imposto il file da leggere al thread di lettura
    reader->setFile(use_path);
    // Imposto il file da leggere alla classe per la gestione della lista
    librariesSearchPath.setSavePath(use_path);
    // Imposto la lista a cui aggiungere i risultati
    reader->setDestinationList(&librariesSearchPath);

    // Avvio il thread
    reader->start();
    // Attendo che termini
    while(reader->isRunning()){

    }

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
    openPackage();
}

void MainWindow::on_actionScheda_home_triggered()
{
    showHomePage();
}

void MainWindow::on_actionSchede_a_sinistra_triggered()
{
    if(ui->actionSchede_a_sinistra->isChecked()){
        ui->widgetManager->setTabPosition(QTabWidget::West);
    }
    else{
        ui->widgetManager->setTabPosition(QTabWidget::North);
    }
}
