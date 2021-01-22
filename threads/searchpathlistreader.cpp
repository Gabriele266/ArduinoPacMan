#include "searchpathlistreader.h"

SearchPathListReader::SearchPathListReader()
{

}

void SearchPathListReader::setDestinationList(LibSearchPathList *l){
    this->list = l;
}

void SearchPathListReader::setFile(QString file){
    this->file_path = file;
}

void SearchPathListReader::run(){
    // Controllo che sia stato specificato il percorso del file
    if(file_path != ""){
        // Controllo che sia stata definita la lista a cui aggiungere i risultati
        if(list != nullptr){
            // Creo l'oggetto file
            QFile file(file_path);

            // Tento di aprire il file
            if(file.open(QIODevice::ReadOnly)){
                // Creo uno stream di testo
                QTextStream str(&file);

                // Leggo riga per riga
                while(!str.atEnd()){
                    // Leggo una riga
                    QString curLine = str.readLine();

                    // Controllo che non si tratti di un commento
                    if(!curLine.startsWith("#")){
                        // Controllo che esista il percorso specificato
                        if(QDir(curLine).exists()){
                            // Aggiungo alla lista
                            list->addPath(curLine);
                            qInfo() << "Aggiunto percorso " << curLine << endl;
                        }
                        else{
                            qInfo() << "Trovato percorso di ricerca non esistente. " << endl;
                        }
                    }
                    // Ignoro il commento
                }
            }
        }
        else{
            qInfo() << "Richiesta lettura di un file di percorsi di ricerca senza aver definito una lista in cui mettere i risultati. " << endl;
        }
    }
    else{
        qInfo() << "Richiesta lettura di un file di percorsi di ricerca senza aver definito il file su cui leggere. " << endl;
    }
}
