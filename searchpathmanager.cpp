#include "searchpathmanager.h"
#include "ui_searchpathmanager.h"

void SearchPathManager::updateItemsCounter(){
    if(entries.count() != 1){
        ui->librariesCount->setText(QString::number(entries.count()) + " Percorsi");
    }
    else{
        ui->librariesCount->setText(QString::number(entries.count()) + " Percorso");
    }
}

SearchPathManager::SearchPathManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchPathManager)
{
    ui->setupUi(this);

    // Imposto il numero di librerie a 0
    updateItemsCounter();

    // Imposto il titolo della finestra
    setWindowTitle("Gestione percorsi di ricerca delle librerie");
}

SearchPathManager::~SearchPathManager()
{
    delete ui;
}

void SearchPathManager::loadFromList(QStringList* baseEntries){
    for(Natural x = 0; x < Natural::make(baseEntries->count(), ElideUnderZero); x ++){
        auto item = new QListWidgetItem();
        item->setText(baseEntries->at(x));
        item->setIcon(QIcon(":/icons/program/Structure.png"));
        ui->pathList->addItem(item);
        qInfo() << "Aggiungo " << baseEntries->at(x) << " indice " << x << endl;
        entries.append(baseEntries->at(x));
    }
    updateItemsCounter();
}

void SearchPathManager::updateItemsView(){
    ui->pathList->clear();
    for(Natural x = 0; x < Natural::make(entries.count(), ElideUnderZero); x++){
        auto i = new QListWidgetItem();
        i->setIcon(QIcon(":/icons/program/Structure.png"));
        i->setText(entries[x]);
        ui->pathList->addItem(i);
    }
}

void SearchPathManager::editItem(Natural index, QString newVal){
    QString old_val = entries[index];

    entries[index] = newVal;

    // Imposto il testo
    ui->pathList->item(index)->setText(newVal);

    emit pathEdited(index, old_val, newVal);
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

        updateItemsCounter();
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

void SearchPathManager::on_addPath_clicked()
{
    // Aggiungo un elemento
    NewSearchPath pt;
    // Avvio
    auto r = pt.exec();

    if(r == QDialog::Accepted){
        addEntry(pt.getSelectedPath());
    }
}

void SearchPathManager::on_removePath_clicked()
{
    // Prendo l'indice dell' oggetto corrente
    int index = ui->pathList->currentIndex().row();
    // Prendo il testo del vecchio elemento
    QString old_item_text = ui->pathList->item(index)->text();

    // Rimuovo l'elemento
    entries.remove(index);

    // Aggiorno la vista
    updateItemsView();

    // Aggiorno il contatore degli elementi
    updateItemsCounter();

    // Emetto il segnale
    emit pathRemoved(old_item_text);
}

void SearchPathManager::on_editCurrent_clicked()
{
    // Prendo l'indice corrente
    Natural curIndex = Natural::make(ui->pathList->currentRow(), ElideUnderZero);

    // Prendo il vecchio testo
    QString old_text = ui->pathList->item(curIndex)->text();

    // Mostro il dialogo per avere il nuovo valore
    NewSearchPath pt(old_text);
    auto r = pt.exec();

    // Controllo il risultato
    if(r == QDialog::Accepted){
        editItem(curIndex, pt.getSelectedPath());
    }
}
