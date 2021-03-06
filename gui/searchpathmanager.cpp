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

    // Check if index exists
    if(index >= 0){
        // Prendo il testo del vecchio elemento
        QString old_item_text = ui->pathList->item(index)->text();

        // Rimuovo l'elemento
        entries.removeAt(index);

        // Aggiorno la vista
        updateItemsView();

        // Aggiorno il contatore degli elementi
        updateItemsCounter();

        // Emetto il segnale
        emit pathRemoved(old_item_text);
    }
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

void SearchPathManager::on_showInBrowser_clicked()
{
    // Ottengo la versione del sistema operativo corrente
    auto os = QOperatingSystemVersion::currentType();

    // Name of the key to search
    QString key_name = "";

    switch(os){
    case QOperatingSystemVersion::Windows:
        key_name = "open-in-files-command-windows";
        break;
    case QOperatingSystemVersion::MacOS:
        key_name = "open-in-files-command-macos";
        break;
    default:
        key_name = "open-in-files-command-linux";
        break;
    }

    // Get the os command
    QString os_command = settings->getKeyValue("os-selective", key_name);

    if(os_command != ""){
        // Get the current item
        int cur = ui->pathList->currentIndex().row();

        if(cur >= 0){
            // Get the item
            QString i = os_command + " \"" + ui->pathList->item(cur)->text() + "\"";
            qInfo() << "Command for open file explorer: " << i << endl;
            // Launch the command
            system(i.toLocal8Bit().data());
        }
    }
}

void SearchPathManager::on_openInTerminal_clicked()
{
    // Ottengo la versione del sistema operativo corrente
    auto os = QOperatingSystemVersion::currentType();

    // Name of the key to search
    QString key_name = "";

    switch(os){
    case QOperatingSystemVersion::Windows:
        key_name = "open-in-terminal-windows";
        break;
    case QOperatingSystemVersion::MacOS:
        key_name = "open-in-terminal-macos";
        break;
    default:
        key_name = "open-in-terminal-linux";
        break;
    }

    // Get the key
    QString c = settings->getKeyValue("os-selective", key_name);

    if(c != ""){
        int cur = ui->pathList->currentIndex().row();

        if(cur >= 0){
            QString i = c + "\"" + ui->pathList->item(cur)->text() + "\"";

            system(i.toLocal8Bit().data());
        }
    }
}
