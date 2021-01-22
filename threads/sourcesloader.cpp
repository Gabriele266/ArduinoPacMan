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

    QDir path = search_path;
    // Controllo che esista
    if(path.exists()){
        // Avvio la ricerca
        appendEntries(root, path);
    }

    // Espando tutti gli elementi
    destination->expandAll();
}

void SourcesLoader::appendEntries(QTreeWidgetItem *item, QDir dir){
    // Ottengo la lista degli elementi figlio
    QStringList lst =  removeRedundant(dir.entryList());

    // Tolgo gli elementi ridondanti
    for(int x = 0; x < lst.count(); x++){
        // Controllo se l'elemento corrente è un file
        QFileInfo f(lst[x]);
        // Oggetto cartella
        // Utile in caso di file system unix o linux
        QDir d(formatPathForOs(dir.path(), QStringList(lst[x])));
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
