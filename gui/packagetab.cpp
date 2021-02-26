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
