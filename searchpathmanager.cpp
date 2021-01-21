#include "searchpathmanager.h"
#include "ui_searchpathmanager.h"

void SearchPathManager::updateLibrariesCounter(){
    if(entries.count() != 1){
        ui->librariesCount->setText(QString::number(entries.count()) + " Librerie");
    }
    else{
        ui->librariesCount->setText(QString::number(entries.count()) + " Libreria");
    }
}

SearchPathManager::SearchPathManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchPathManager)
{
    ui->setupUi(this);

    // Imposto il numero di librerie a 0
    updateLibrariesCounter();
}

SearchPathManager::~SearchPathManager()
{
    delete ui;
}

void SearchPathManager::loadFromList(QStringList baseEntries){
    for(int x = 0; x < baseEntries.count(); x ++){
        auto item = new QListWidgetItem();
        item->setText(baseEntries[x]);
        item->setIcon(QIcon(":/icons/program/Structure.png"));
        ui->pathList->addItem(item);
    }
    updateLibrariesCounter();
}

void SearchPathManager::addEntry(QString path){
    // Controllo che non esista nessuna altra entry con questo nome
    if(notExists(path, entries)){
        // Aggiungo alla lista delle entry
        entries.append(path);
        auto item = new QListWidgetItem();
        item->setText(path);
        item->setIcon(QIcon(":/icons/program/Structure.png"));
        ui->pathList->addItem(item);

        updateLibrariesCounter();
        // Invio il segnale di aggiunta del nuovo elemento
        emit pathAdded(path);
    }
    else{
        QMessageBox::critical(this, "Errore", "Attenzione, si è tentato di aggiungere un percorso che si trova già nella lista di ricerca. ");
    }
}

QStringList SearchPathManager::getEntriesList(){
    return entries;
}

void SearchPathManager::onEntryAccept(QString entry){
    addEntry(entry);
}

void SearchPathManager::on_addPath_clicked()
{
    // Aggiungo un elemento
    NewSearchPath pt;
    // Connetto il gestore
    QObject::connect(&pt, &NewSearchPath::pathAccepted, this, &SearchPathManager::onEntryAccept);
    // Avvio
    pt.exec();
}

void SearchPathManager::on_removePath_clicked()
{
    // Prendo l'indice dell' oggetto corrente
    Natural index = ui->pathList->currentIndex().row();

    // Rimuovo l'elemento
    entries.remove(index);
}
