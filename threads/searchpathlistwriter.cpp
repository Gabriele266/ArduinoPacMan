#include "searchpathlistwriter.h"

SearchPathListWriter::SearchPathListWriter()
{

}

void SearchPathListWriter::setLibraryList(LibSearchPathList *info){
    searchPathList = info;
}

void SearchPathListWriter::run(){
    LibWritingEnd exit_code;
    // Controllo che sia stata impostata una lista di percorsi da scrivere
    if(searchPathList != nullptr){
        // Controllo che sia presente qualcosa da scrivere
        if(searchPathList->getListCount() > 0){
            // Controllo che il percorso sia plausibile
            if(searchPathList->getSavePath() != ""){
                // Creo il file
                QFile file = searchPathList->getSavePath();

                // Tento di aprirlo in scrittura
                if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
                    // Sono riuscito ad aprirlo
                    // Creo uno stream di testo
                    QTextStream str(&file);

                    // Metto un commento
                    str << "# arduinopacman library path search file#" << endl;
                    // Avvio la scrittura dei percorsi
                    for(Natural x = 0; x < searchPathList->getListCount(); x++){
                        str << searchPathList->getPath(x) << endl;
                    }
                    // Imposto lo stato di uscita
                    exit_code = Success;
                }
                else{
                    exit_code = FileAccessError;
                }
            }
            else{
                exit_code = PassedPathNotExisting;
            }
            // Creo un file per il
        }
        else{
            exit_code = LibrarySearchPathEmpty;
        }
    }
    else{
        exit_code = NoListPassed;
    }
}
