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
