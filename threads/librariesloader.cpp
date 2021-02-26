#include "librariesloader.h"

LibrariesLoader::LibrariesLoader()
{

}

void LibrariesLoader::setDestination(QTreeWidget *dest){
    destination = dest;
}

void LibrariesLoader::setSearchPath(QString path){
    this->path = path;
}

void LibrariesLoader::setLibrariesDestination(QList<Library *> *libraries){
    this->libraries = libraries;
}

void LibrariesLoader::run(){
    // Controllo il percorso
    QDir dir(path);

    // Controllo che esista
    if(dir.exists()){
        // Ottengo la lista di tutti i nomi di cartella presenti al suo interno
        QStringList entries = removeRedundant(dir.entryList());

        // Scorro tutti gli elementi
        for(int x = 0; x < entries.count(); x++){
            // Ottengo il percorso completo
            QDir complete = formatPathForOs(path, QStringList(entries[x]));
            // Controllo che esista
            if(complete.exists()){
                // Potrei aver trovato una libreria
                Library *lib = new Library();
                // Imposto il percorso completo
                lib->setCompletePath(complete.path());
                // Inizializzo la libreria
                lib->init();
                // La aggiungo all' array
                libraries->append(lib);
                // Aggiungo un elemento per la libreria nell albero
                auto *item = new QTreeWidgetItem();
                item->setText(0, entries[x]);
                item->setText(1, "Libreria");
                item->setText(2, complete.path());
                item->setIcon(0, QIcon(":/icons/program/Library.png"));
                destination->addTopLevelItem(item);
            }
        }
    }
}
