#include "sourcesloader.h"

SourcesLoader::SourcesLoader()
{
}

void SourcesLoader::run(){
    // Creo un oggetto root
    auto *root = new QTreeWidgetItem();
    root->setText(0, "File");
    root->setText(1, "Albero file e cartelle");

    // Aggiungo il nodo root
    destination->addTopLevelItem(root);

    // Creo un oggetto cartella in cui mostrare i file sorgenti
    QDir path(search_path);

    // Controllo che esista
    if(path.exists()){
        // Avvio la ricerca
        appendEntries(root, path);
    }
    else{
        QMessageBox::critical(nullptr, "Errore grave", "Errore grave: il percorso scelto per il caricamento dei sorgenti non esiste. ");
    }

    // Espando tutti gli elementi
    destination->expandAll();
    // Controllo che la funzione da chiamare esista
    if(function != nullptr){

    }
}

void SourcesLoader::setExitFunction(void (PackageManager::*pointer)()){
    function = pointer;
}

void SourcesLoader::appendFileIfSource(QString file){
    // Creo l'oggetto sorgente
    Source *src = new Source();
    src->setCompleteFile(file);

    if(src->isSource()){
        qInfo() << "File sorgente trovato: " << src->getName() <<
                   " tipologia di sorgente: " <<
                   Source::sourceTypeToString(src->getSourceType()) << endl;

        if(package != nullptr){
            package->addSource(src);
        }
        else{
            qInfo() << "Impossibile aggiungere il sorgente " << src->getName() << " siccome non è stato specificato nessun"
            "pacchetto a cui aggiungerlo. " << endl;
        }
    }
}

void SourcesLoader::appendEntries(QTreeWidgetItem *item, QDir dir){
    // Ottengo la lista degli elementi figlio
    QStringList lst =  removeRedundant(dir.entryList());

    // Tolgo gli elementi ridondanti
    for(int x = 0; x < lst.count(); x++){
        // Percorso completo del file o cartella
        QString complete_path = formatPathForOs(dir.path(), QStringList(lst[x]));
        // Controllo se l'elemento corrente è un file
        QFileInfo f(complete_path);
        // Oggetto cartella
        // Utile in caso di file system unix o linux
        QDir d(complete_path);
        // Controllo se si tratta di un file
        if(!d.exists()){
            // Aggiungo il file
            auto *elem = new QTreeWidgetItem();
            elem->setText(0, f.fileName());
            elem->setText(1, "File");
            elem->setText(2, f.absoluteFilePath());
            elem->setIcon(0, QIcon(":/icons/browsing/file_icon.png"));
            // Aggiungo al nodo
            item->addChild(elem);

            // Aggiungo il sorgente al pacchetto
            appendFileIfSource(f.absoluteFilePath());
        }
        // Si tratta di una cartella
        else{
            // Si tratta di una cartella
            // Controllo che non siano cartelle simboliche
            if(lst[x] != "." && lst[x] != ".." ){
                auto *elem = new QTreeWidgetItem();
                // Percorso della cartella corrente
                elem->setText(0, lst[x]);
                elem->setText(1, "Cartella");
                elem->setText(2, formatPathForOs(dir.path(), QStringList(lst[x])));
                elem->setIcon(0, QIcon(":/icons/browsing/folder_icon.png"));
                item->addChild(elem);

                // Lancio di nuovo la ricerca
                appendEntries(elem, d);
            }
        }
    }
}

void SourcesLoader::setDestination(QTreeWidget *item){
    destination = item;
}

void SourcesLoader::setSearchPath(QString path){
    search_path = path;
}
