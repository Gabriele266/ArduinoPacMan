#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

        // Connetto i thread
        QObject::connect(settingsReader, &SettingsReader::finished, this, &MainWindow::loadSearchPathFromFile);
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

    // Mostro la scheda home
    showHomePage();

}

void MainWindow::showHomePage(){
    // Aggiungo il tab home
    HomePage *home = new HomePage( nullptr);
    ui->widgetManager->addTab(home, "Home");
    tabs.append(home);

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
    // Cartella in cui aprire il file browser
    QString file_browser_base_path = resolvePath(settings.getKeyValue("paths", "default-package-path"));

    // Controllo se esiste un valore
    if(file_browser_base_path == ""){
        // Uso il percorso home del sistema operativo
        file_browser_base_path = getHomePath();
    }

    qInfo() << "Apro browser " << file_browser_base_path << endl;
    // Chiedo una directory in cui cercare il pacchetto partendo dal percorso giusto
    QString dir = QFileDialog::getExistingDirectory(this, "Selezionare la cartella del pacchetto", file_browser_base_path);

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
        // Pacchetto letto
        Package* pack = reader->getPackage();

        // Controllo che il pacchetto sia stato letto correttamente
        if(pack != nullptr){
            // Controllo che non esista già nella vista
            if(!isOpenedPackage(pack)){
                // Aggiungo il pacchetto
                auto p = addPackageToView(pack);
                // Controllo che sia stato aggiunto
                if(p != nullptr){
                    tabs.append(p);
                    // Aggiungo il pacchetto alla lista dei pacchetti
                    packageList.append(pack);
                    qInfo() << "Pacchetto caricato con successo: " << pack->getName() << endl;
                }
            }
            else{
                // Mostro un warning
                QMessageBox::warning(this, "Attenzione", "Il pacchetto che si è cercato di aprire è già aperto. ");
                qInfo() << pack->getName() << " tentativo di aprirlo due volte. " << endl;
            }
        }
        else{
            // Mostro errori
            QMessageBox::critical(this, "Errore", "Impossibile aprire il pacchetto. ");
            qInfo() << "Errore nella apertura del pacchetto. " << endl;
        }
    }
}

void MainWindow::updateTitleInfo(){
    // Titolo base
    QString title = QString("ArduinoPacMan %1 ").arg(ARDUINO_PACMAN_VERSION.toString());
    // Determino se il tab corrente è un pacchetto
    if(currentTabIsPackage()){
        // Scrivo il nome del pacchetto
        title += "| ";
        title += getCurrentPackage()->getName();
    }
    else{
        title += "| Scheda home";
    }
    // Imposto il titolo alla finestra
    setWindowTitle(title);
}

void MainWindow::updateStatusBar(){
    // Scrivo il numero di pacchetti aperti
    statusBar->setPackagesCount(packageList.count());

    // Controllo se il tab corrente è un pacchetto
    if(currentTabIsPackage()){
        // Imposto il percorso del pacchetto corrente
        statusBar->setCurrentPackagePath(getCurrentPackage()->getSavePath());
        statusBar->setLibraryCount(getCurrentPackage()->getLibraryCount());
    }
    else{
        statusBar->setCurrentPackagePath("Scheda home");
        statusBar->setLibraryCount(0);
    }
}

bool MainWindow::currentTabIsPackage(){
    if(getCurrentPackage() != nullptr){
        return true;
    }
    return false;
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

        // Aggiungo il pacchetto alla lista
        packageList.append(package);

        // Aggiungo il pacchetto al gestore
        tabs.append(addPackageToView(package));
    }

    // Aggiorno il titolo
    updateTitleInfo();
    // Aggiorno la barra di stato
    updateStatusBar();
}
bool MainWindow::isOpenedPackage(Package *package){
    for(int x = 0; x < packageList.count(); x++){
        if(package->equals(packageList[x])){
            return true;
        }
    }
    return false;
}

Tab* MainWindow::addPackageToView(Package *pack){
    // Controllo che non sia un puntatore nullo
    if(pack != nullptr){
        // Controllo che abbia un nome e un percorso
        if(pack->getName() != "" && pack->getCompletePath() != ""){
            // Imposto l'indice del pacchetto
            pack->addTag(QString::number(packageList.count()));
            // Mostro il pacchetto
            PackageTab *tab = new PackageTab(pack);
            // Imposto i tag del tab
            tab->setTags("<package>");
            // Aggiungo
            ui->widgetManager->addTab(tab, pack->getName());

            // Percorso dei sorgenti
            QString sources_path = pack->getSourcesPath();
            // File sorgente principale
            QString main_file_path = pack->getMainSourcePath();

            // Controllo che il pacchetto abbia dei sorgenti
            if(sources_path != "" && QDir(sources_path).exists()){
                // Controllo che abbia un file principale
                if(main_file_path != "" && QFile::exists(main_file_path)){
                    // Carico i suoi sorgenti
                    auto *loader = new SourcesLoader();
                    loader->setDestination(tab->getFileBrowser());
                    loader->setSearchPath(pack->getSourcesPath());
                    qInfo() << "Carico sorgenti per il percorso " << pack->getSourcesPath() << endl;
                    loader->setPackage(pack);

                    // Avvio il thread
                    loader->start(QThread::HighPriority);

                    // Controllo che il file impostato come sorgente principale sia effettivamente un sorgente
                    if(SourceInfo::fileIsSource(main_file_path)){
                        // Avvio il caricamento dei sorgenti per il pacchetto
                        auto *lister = new SrcDependencyLister();
                        // Imposto il pacchetto
                        lister->setPackage(pack);
                        // Imposto il widget
                        lister->setWidget(tab->getDependencyBrowser());
                        lister->start();
                    }
                    else{
                        // Non si tratta di un vero sorgente supportato
                        QMessageBox::critical(this, "Errore", "Il file impostato come sorgente principale ha come estensione \n" + getFileExtension(main_file_path) + " che non rappresenta un file sorgente supportato. \nNon e' possibile caricare le dipendenze da questo file. ");
                    }
                }
                else{
                    QMessageBox::warning(this, "Attenzione", "Il pacchetto che si è tentato di aprire non ha un file sorgente principale o, se è stato impostato, il file non esiste sul disco. ");
                    qInfo() << "Pacchetto " << pack->getName() << " senza file principale corretto. " << endl;
                }
            }
            else{
                QMessageBox::warning(this, "Attenzione", "Il pacchetto che si è tentato di aprire non ha dei sorgenti associati. Non verranno caricate dipendenze fino a quando non saranno impostati. ");
                qInfo() << "Pacchetto " << pack->getName() << " senza sorgenti" << endl;
            }

            // Add the found libraries to the object view
            for(Natural x = 0; x < mk(foundLibraries.count()); x++){
                tab->addLibraryToList(foundLibraries[x]);
            }

            return tab;
        }
        else{
            QMessageBox::critical(this, "Errore", "Errore durante l'apertura del pacchetto. Non è stato possibile leggerlo correttamente o non si trattava di un pacchetto formattato correttamente. ");
        }
    }
    return nullptr;
}

void MainWindow::on_actionNuova_finestra_triggered()
{
    // Creo una nuova finestra
    auto *mainWin = new MainWindow();
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

void MainWindow::loadSearchPathFromFile(){
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

    // Connect the events
    QObject::connect(reader, &SearchPathListReader::finished, this, &MainWindow::loadLibraryList);

    qInfo() << "Caricati percorsi ricerca librerie. " << endl;
}

void MainWindow::loadLibraryList(){
    // Avvio i vari thread per il caricamento delle informazioni per le librerie
    for(Natural x = 0; x < mk(librariesSearchPath.getListCount()); x++){
        // Creo il thread
        auto *loader = new LibrariesLoader();
        loader->setLibrariesDestination(&foundLibraries);
        loader->setSearchPath(librariesSearchPath.getPath(x));
        loader->start();
    }
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

int MainWindow::getPackageIndex(Natural tabIndex){
    // Tab corrente
    Tab *curTab = nullptr;
    // Numero di pagine home trovate
    Natural homeFound = 0;
    // Numero di pacchetti trovati
    int packagesFound = -1;
    // Scorro tutti i tab
    for(Natural x = 0; x <= tabIndex; x++){
        if(mk(tabs.count()) > x){
            // Ottengo il tab con quell' indice
            curTab = tabs[x];

            if(curTab != nullptr){
                if(curTab->getInfo() == "<home>"){
                    homeFound ++;
                }
                else{
                    packagesFound ++;
                }
            }
        }
    }

    // Controllo che esista un elemento con quell' indice
    if(mk(packageList.count()) > packagesFound && packagesFound >= 0){
        return packagesFound;
    }
    return -1;
}

void MainWindow::on_widgetManager_currentChanged(int index)
{   
    // Aggiorno la barra di stato
    updateStatusBar();
    // Aggiorno il titolo
    updateTitleInfo();
}

Package* MainWindow::getCurrentPackage(){
    // Indice del pacchetto nella sua lista
    int index = getPackageIndex(ui->widgetManager->currentIndex());
    if(index >= 0 && packageList.count() > index){
        return packageList[index];
    }
    return nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
    // Rimuovo tutti i pacchetti
    for(Natural x = 0; x < mk(packageList.count()); x++){
        delete packageList[x];
    }
}

void MainWindow::on_actionPropriet_pacchetto_triggered()
{
    // Ottengo il pacchetto corrente
    auto cur = getCurrentPackage();

    // Controllo se effettivamente esiste
    if(cur != nullptr){
        PackageInfo *info = new PackageInfo(cur);
        info->show();
    }
    else{
        QMessageBox::critical(this, "Errore", "Per visualizzare le proprietà di un pacchetto è necessario prima selezionarne uno nel controllo multi-tab o aprirne uno nuovo. ");
    }
}

Package* MainWindow::getPackageFromTabIndex(Natural tabIndex){
    // Ottengo il numero del pacchetto
    int num = getPackageIndex(tabIndex);
    if(num > 0){
        // Controllo se esiste un pacchetto con quell' indice
        if(packageList.count() > num){
            return packageList[num];
        }
        qInfo() << "Errore: numero di pacchetto rintracciato a partire dall' indice tab " << tabIndex << " ma non corrisponde a nessun pacchetto in memoria. " << endl;
        return nullptr;
    }
    return nullptr;
}

void MainWindow::on_widgetManager_tabCloseRequested(int index)
{
    removeTab(index);
}

void MainWindow::removeTab(Natural tabIndex){
    // Ottengo l'indice del pacchetto
    int pack = getPackageIndex(tabIndex);
    if(pack >= 0 && pack < packageList.count()){
        // Tolgo il pacchetto dalla memoria
        packageList.removeAt(pack);
    }
    // Rimuovo il tab
    ui->widgetManager->removeTab(tabIndex);
}

void MainWindow::on_actionChiudi_tutte_le_schede_aperte_triggered()
{
    int dim = ui->widgetManager->count();
    qInfo() << "Numero schede: " << dim << endl;
    for(int x = 0; x < dim; x++){
        removeTab(x);
    }
    // Aggiorno il titolo
    updateTitleInfo();
    // Aggiorno la barra di stato
    updateStatusBar();
}
