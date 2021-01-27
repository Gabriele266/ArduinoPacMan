#include "sourceslister.h"

SourcesLister::SourcesLister(Source* file, QList<Dependency*>* results){
    startFile = file;
    resultsList = results;
}

SourcesLister::SourcesLister() : SourcesLister(nullptr, nullptr)
{
    // Nothing
}

void SourcesLister::appendDependencyToWidget(Dependency *dep){
    // Controllo che esista un controllo
    if(widget != nullptr){
        if(dep != nullptr){
            QTreeWidgetItem *item = new QTreeWidgetItem();
            item->setText(0, dep->getLibraryName());

        }
    }
}

void SourcesLister::run(){
    // Creo l'oggetto file
    QFile file(startFile->getCompleteFile());

    if(file.open(QIODevice::ReadOnly)){
        // Creo uno stream di testo
        QTextStream str(&file);
        // Contatore del numero di riga corrente
        Natural current_row = 0;

        // Processo riga per riga
        while(!str.atEnd()){
            // Leggo la riga corrente
            QString curLine = str.readLine();
            // Controllo se si tratta di una direttiva al preprocessore per una inclusione di libreria
            if(curLine.startsWith("#include")){
                // Prendo il contenuto dell' header richiesto
                QString head = curLine.mid(curLine.indexOf('<') + 1, curLine.indexOf('>') - 1);
                // Rimuovo gli spazi
                head = head.remove('>');
                qInfo() << "Header richiesto: " << head;
                // Prendo il nome della libreria
                QStringList div = head.split('.');
                if(div.count() == 2){
                    QString lib_name = div[0];

                    // Formatto una dipendenza
                    Dependency *d = new Dependency();
                    d->setLibraryName(lib_name);
                    d->setHeaderName(head);
                    // Aggiungo la dipendenza alla lista
                    resultsList->append(d);
                    // Aggiungo la dipendenza al sorgente
                    startFile->appendDependency(d);
                }
            }
            current_row ++;
        }
    }
}
