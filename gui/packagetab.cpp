#include "packagetab.h"
#include "ui_packagetab.h"

PackageTab::PackageTab(Package *package, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PackageTab)
{
    ui->setupUi(this);
    this->package = package;

    // Imposto le informazioni per riconoscere il tab
    setName("Package");
    setInfo("<package>");

    // Formatto il menu contestuale per le librerie
    librariesContextMenu = new QMenu(this);
    librariesContextMenu->addAction(ui->actionInformazioni_libreria);
    librariesContextMenu->addAction(ui->actionMostra_in_visualizzatore);
    librariesContextMenu->addSeparator();
    librariesContextMenu->addAction(ui->actionAggiungi_al_pacchetto);
    librariesContextMenu->addAction(ui->actionNascondi);
    librariesContextMenu->addAction(ui->actionIgnora);
    librariesContextMenu->addAction(ui->actionNotALibrary);
    librariesContextMenu->addSeparator();
    librariesContextMenu->addAction(ui->actionApri_percorso);
    librariesContextMenu->addAction(ui->actionApri_nel_terminale);
    librariesContextMenu->addSeparator();
    librariesContextMenu->addAction(ui->actionApri_documentazione);
    librariesContextMenu->addAction(ui->actionApri_esempi);
    librariesContextMenu->addAction(ui->actionApri_keywords);

    // Formatto il menu contestuale per la visualizzazione file
    filesContextMenu = new QMenu(this);
    filesContextMenu->addAction(ui->actionInformazioni);
    filesContextMenu->addAction(ui->actionLista_tag);
    filesContextMenu->addAction(ui->actionImposta_flag);
    filesContextMenu->addSeparator();
    filesContextMenu->addAction(ui->actionAggiorna_vista);
    filesContextMenu->addSeparator();
    filesContextMenu->addAction(ui->actionApri_in_visualizzatore);
    filesContextMenu->addAction(ui->actionApri_con_applicazione_di_sistema);
    filesContextMenu->addAction(ui->actionApri_in_terminale);
    filesContextMenu->addSeparator();
    filesContextMenu->addAction(ui->actionCopia);
    filesContextMenu->addAction(ui->actionCopia_contenuto_in_appunti);
    filesContextMenu->addAction(ui->actionCopia_contenuto);
    filesContextMenu->addSeparator();
    filesContextMenu->addAction(ui->actionIncolla);
    filesContextMenu->addAction(ui->actionIncolla_all_interno);
    filesContextMenu->addAction(ui->actionSposta);
    filesContextMenu->addSeparator();
    filesContextMenu->addAction(ui->actionImporta);
    filesContextMenu->addAction(ui->actionEsporta);
    filesContextMenu->addSeparator();
    filesContextMenu->addAction(ui->actionElimina);
    filesContextMenu->addAction(ui->actionElimina_contenuto);

    // Formatto il menu contestuale per la visualizzazione dipendenze
    dependencyContextMenu = new QMenu(this);
    dependencyContextMenu->addAction(ui->actionMostra_informazioni);
    dependencyContextMenu->addAction(ui->actionMostra_libreria);
    dependencyContextMenu->addSeparator();
    dependencyContextMenu->addAction(ui->actionApri_file_dipendenza);
    dependencyContextMenu->addAction(ui->actionApri_file_sorgente_in_ambiente);
    dependencyContextMenu->addSeparator();
    dependencyContextMenu->addAction(ui->actionIgnora_dipendenza);
    dependencyContextMenu->addAction(ui->actionAbilita_dipendenza);
    dependencyContextMenu->addSeparator();
    dependencyContextMenu->addAction(ui->actionVisualizzazione_compatta);

    // Formatto il menu contestuale per la visualizzazione delle librerie aggiunte
    addedLibrariesContextMenu = new QMenu(this);
    addedLibrariesContextMenu->addAction(ui->actionInformazioniLibreria);
    addedLibrariesContextMenu->addSeparator();
    addedLibrariesContextMenu->addAction(ui->actionApri_percorso_libreria);
    addedLibrariesContextMenu->addAction(ui->actionApriLibInVisualizzatore);
    addedLibrariesContextMenu->addAction(ui->actionApri_libreria_terminale);
    addedLibrariesContextMenu->addSeparator();

    addedLibrariesContextMenu->addAction(ui->actionApri_esempi_lib);
    addedLibrariesContextMenu->addAction(ui->actionApri_keywords_lib);
    addedLibrariesContextMenu->addAction(ui->actionApri_documentazione_lib);
    addedLibrariesContextMenu->addSeparator();
    addedLibrariesContextMenu->addAction(ui->actionRimuoviLibreria);
}

void PackageTab::setTags(QString tags){
    tag = tags;
}

QString PackageTab::getTags(){
    return tag;
}

QTreeWidget* PackageTab::getFileBrowser(){
    return ui->fileBrowser;
}

QTreeWidget *PackageTab::getDependencyBrowser()
{
    return ui->dependencyBrowser;
}

Package* PackageTab::getPackage(){
    return package;
}

PackageTab::~PackageTab()
{
    delete ui;
}

QTreeWidget* PackageTab::getFoundLibrariesManager(){
    return ui->libraryBrowser;
}

void PackageTab::on_libraryBrowser_customContextMenuRequested(const QPoint &pos)
{
    // Mostro il menu
    librariesContextMenu->popup(ui->libraryBrowser->mapToGlobal(pos));
}

void PackageTab::on_fileBrowser_customContextMenuRequested(const QPoint &pos)
{
    filesContextMenu->popup(ui->fileBrowser->mapToGlobal(pos));
}

void PackageTab::on_dependencyBrowser_customContextMenuRequested(const QPoint &pos)
{
    dependencyContextMenu->popup(ui->dependencyBrowser->mapToGlobal(pos));
}

void PackageTab::on_packageLibraryViewer_customContextMenuRequested(const QPoint &pos)
{
    addedLibrariesContextMenu->popup(ui->packageLibraryViewer->mapToGlobal(pos));
}

void PackageTab::on_actionInformazioni_triggered()
{
    // Prendo la libreria indicata dal elemento corrente
    Natural cur_item_index = ui->libraryBrowser->currentIndex().row();
}

void PackageTab::addLibraryToPackage(Library *lib){
    // Check if package already has this library
    if(!package->existsLibrary(lib)){
        // Add the library to the list
        package->addLibrary(lib);
        // Create a widget to display it
        ui->packageLibraryViewer->addTopLevelItem(formatLibraryWidget(lib));
    }
    else{
        QMessageBox::warning(this, "Attenzione", "La libreria selezionata è già stata aggiunta al pacchetto. ");
    }
}

void PackageTab::addLibraryToList(Library *library){
    if(library != nullptr){
        // Add library to list
        libraries.append(library);
        // Create the widget to display it
        // Add the item
        ui->libraryBrowser->addTopLevelItem(formatLibraryWidget(library));
    }
}

Library* PackageTab::getSelectedLibraryFromList(){
    // Get the current index
    int cur = ui->libraryBrowser->currentIndex().row();
    // Get the library
    if(cur >= 0 && cur <= libraries.count()){
        return libraries.at(cur);
    }
    else{
        return nullptr;
    }
}

QTreeWidgetItem* PackageTab::formatLibraryWidget(Library *lib){
    if(lib != nullptr){
        auto *item = new QTreeWidgetItem();
        item->setText(0, lib->getName());
        item->setText(1, "Libreria");
        item->setText(2, lib->getPath());
        item->setIcon(0, QIcon(":/icons/program/Library.png"));
        return item;
    }
    return nullptr;
}

void PackageTab::on_actionAggiungi_al_pacchetto_triggered()
{
    // Get current library
    auto l = getSelectedLibraryFromList();
    if(l != nullptr){
        // Add the library to the package
        addLibraryToPackage(l);
    }
}

void PackageTab::on_actionNotALibrary_triggered()
{
    // Get the current index
    int cur = ui->libraryBrowser->currentIndex().row();
    if(cur >= 0){
        libraries.removeAt(cur);
        delete ui->libraryBrowser->takeTopLevelItem(cur);
    }
}

void PackageTab::on_actionInformazioniLibreria_triggered()
{
    // Null for now
}

void PackageTab::on_actionInformazioni_libreria_triggered()
{
    auto *tab = new LibraryTab();
    auto l = getSelectedLibraryFromList();

    if(l != nullptr){
        // Set the tab library
        tab->setLibrary(l);
        // Set the package that owns it
        tab->setPackage(package);
        // Require new tab display
        emit libraryTabAdd(tab);
    }
}
